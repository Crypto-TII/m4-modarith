#!/usr/bin/env python3
#
#  This program is free software. It comes without any
#  warranty, to the extent permitted by applicable law.
#

import socket
import time
import re
import sys


class Stream:
    """
    Stream of messages for one of the 32 ITM channels.

    ITM Trace messages can be output on one of 32 channels. The stream class
    contains a byte buffer for one of these channels. Once a newline character
    is received, the buffer is dumped to stdout. Also, there is an optional
    string that is prepended to the start of each line. This is useful for
    using different channels for different logging levels.

    For example, one might use channel 0 for info messages, channel 1 for
    warnings, and channel 2 for errors. One might like to use "INFO: ",
    "WARNING: ", and "ERROR: " as the headers for these channels. The debugger
    can enable and disable these channels on startup if you want to only see
    error messages. This would actually prevent the info and warning messages
    from being generated by the processor, which will save time in the code
    because ITM routines are blocking.

    Each stream also has the option to echo to the GDB console. Simply pass
    the socket connected to the Tcl server to the constructor

    """

    # Max number of characters for a stream before a newline needs to occur
    MAX_LINE_LENGTH = 1024

    def __init__(self, id, header="", tcl_socket=None):
        self.id = id
        self._buffer = []
        self._header = header
        self.tcl_socket = tcl_socket

    def add_char(self, c):
        if len(self._buffer) >= self.MAX_LINE_LENGTH:
            self._output(
                "SWO_PARSER.PY WARNING: stream "
                + str(self.id)
                + " received "
                + str(self.MAX_LINE_LENGTH)
                + " bytes without receiving a newline. Did you forget one?"
            )
            self._output(self._header + "".join(self._buffer) + c)
            self._buffer = []
            return

        if c == "\n":
            self._output(self._header + "".join(self._buffer))
            self._buffer = []
            return

        self._buffer.append(c)

    def add_chars(self, s):
        for c in s:
            self.add_char(c)

    def _output(self, s):
        # Match with regex below and call sys.exit with the return code
        if m := re.match(
            "^---------- Program exited with return code ([0-9]+) ----------$",
            s,
        ):
            sys.exit(int(m.group(1)))
        else:
            print(s, flush=True)
            return


class StreamManager:
    """
    Manages up to 32 byte streams.

    This class contains a dictionary of streams indexed by their stream id. It
    is responsible for parsing the incoming data, and forwarding the bytes to
    the correct stream.

    """

    def __init__(self):
        self.streams = dict()
        self._itmbuffer = b""

    def add_stream(self, stream):
        self.streams[stream.id] = stream

    def parse_tcl(self, line):
        r"""
        When OpenOCD is configured to output the trace data over the Tcl
        server, it periodically outputs a string (terminated with \r\n) that
        looks something like this:

        type target_trace data 01480165016c016c016f0120015401720161016301650121010a

        The parse_tcl method turns this into the raw ITM bytes and sends it to
        parse_itm_bytes.

        """
        if line.startswith(b"type target_trace data ") and line.endswith(b"\r\n"):
            itm_bytes = int(line[23:-2], 16).to_bytes(
                len(line[23:-2]) // 2, byteorder="big"
            )
            self.parse_itm_bytes(itm_bytes)

    def parse_itm_bytes(self, bstring):
        """
        Parses ITM packets based on the format discription from ARM
        http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0314h/Chdbicbg.html

        """

        bstring = self._itmbuffer + bstring
        self._itmbuffer = b""

        while len(bstring) > 0:
            header = bstring[0]
            # The third bit of a header must be zero, and the last two bits
            # can't be zero.
            if header & 0x04 != 0 or header & 0x03 == 0:
                bstring = bstring[1:]
                continue

            payload_size = 2 ** (header & 0x03 - 1)
            stream_id = header >> 3

            if payload_size >= len(bstring):
                self._itmbuffer = bstring
                return

            if stream_id in self.streams:
                s = bstring[1 : payload_size + 1].decode("ascii", errors="replace")
                self.streams[stream_id].add_chars(s)

            bstring = bstring[payload_size + 1 :]


#### Main program ####

# Set up the socket to the OpenOCD Tcl server
HOST = "localhost"
PORT = 50001
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as tcl_socket:
    retries = 0
    while retries < 100:
        try:
            tcl_socket.connect((HOST, PORT))
            print(
                "SWO client successfully connected to OpenOCD on %s:%d" % (HOST, PORT),
                flush=True,
            )

        except socket.error:
            retries += 1
            if retries == 100:
                print(
                    "Failed to connect to OpenOCD on %s:%d" % (HOST, PORT),
                    flush=True,
                )
                sys.exit(1)
            time.sleep(0.1)
            tcl_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            continue
        else:
            break

    # Create a stream manager and add three streams
    streams = StreamManager()
    streams.add_stream(Stream(0, "", tcl_socket))
    streams.add_stream(Stream(1, "WARNING: "))
    streams.add_stream(Stream(2, "ERROR: ", tcl_socket))

    # Enable the tcl_trace output
    tcl_socket.sendall(b"tcl_trace on\n\x1a")

    tcl_buf = b""
    while True:
        # Wait for new data from the socket
        data = b""
        while len(data) == 0:
            try:
                data = tcl_socket.recv(1024)
            except BlockingIOError:
                time.sleep(0.1)

        tcl_buf = tcl_buf + data

        # Tcl messages are terminated with a 0x1A byte
        temp = tcl_buf.split(b"\x1a", 1)
        while len(temp) == 2:
            # Parse the Tcl message
            streams.parse_tcl(temp[0])

            # Remove that message from tcl_buf and grab another message from
            # the buffer if the is one
            tcl_buf = temp[1]
            temp = tcl_buf.split(b"\x1a", 1)

    # Turn off the trace data before closing the port
    # XXX: There currently isn't a way for the code to actually reach this line
    tcl_socket.sendall(b"tcl_trace off\n\x1a")
