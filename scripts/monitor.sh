#!/bin/bash
source select_host_board.sh

if [ $# -eq 1 ]; then
    if [ $1 == "fast" ]; then
        CLOCK_FREQUENCY=$CLOCK_FREQUENCY_FAST
    elif [ $1 == "benchmark" ]; then
        CLOCK_FREQUENCY=$CLOCK_FREQUENCY_BENCHMARK
    else
        echo "Usage: $0 <clock speed> # clock speed options: \"fast\" or \"benchmark\""
        exit 1
    fi
else
    echo "Usage: $0 <clock speed> # clock speed options: \"fast\" or \"benchmark\""
    exit 1
fi

if [[ -z ${STLINK_SERIAL} ]]
then
    STLINK_SERIAL_ARG=""
else
    STLINK_SERIAL_ARG="-s${STLINK_SERIAL}"
fi

if [[ $(st-info --probe) == "Found 0 stlink programmers" ]]
then
    ssh -t $REMOTE_HOST 'timeout 60 st-trace '${STLINK_SERIAL_ARG}' -c'${CLOCK_FREQUENCY}'m'
else
    st-trace ${STLINK_SERIAL_ARG} -c${CLOCK_FREQUENCY}
fi

