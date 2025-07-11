#!/bin/bash
source select_host_board.sh

if [[ -z ${STLINK_SERIAL} ]]
then
    STLINK_SERIAL_ARG=""
else
    STLINK_SERIAL_ARG="-c \"adapter serial ${STLINK_SERIAL}\""
fi

if [[ $1 == "" ]]
then
    echo "Usage: $0 <command> [args]"
    echo "       <command>: debug | run"
    echo "       if <command> is \"run\", [args] is the path to the ELF file to be flashed and run"
    exit 1
elif [[ $1 == "debug" ]]
then
    ssh \
        -L 50000:127.0.0.1:50000 \
        -L 50001:127.0.0.1:50001 \
        -L 50003:127.0.0.1:50003 \
        -t $REMOTE_HOST \
        'openocd -f '${BOARD_CFG_FILE}' '${STLINK_SERIAL_ARG}' -c "bindto 0.0.0.0" -c "gdb_port 50000" -c "tcl_port 50001"'
elif [[ $1 == "run" ]]
then
    TEMP_FILE_ELF=$(ssh $REMOTE_HOST 'mktemp --suffix=.elf')
    scp $2 $REMOTE_HOST:$TEMP_FILE_ELF
    ssh \
        -L 50001:127.0.0.1:50001 \
        -L 50002:127.0.0.1:50002 \
        -t $REMOTE_HOST \
        'openocd -f '${BOARD_CFG_FILE}' '${STLINK_SERIAL_ARG}' -c "bindto 0.0.0.0" -c "tcl_port 50001" -c "telnet_port 50002" -c "program '${TEMP_FILE_ELF}' verify reset"'
    # ssh \
    #     -L 50001:127.0.0.1:50001 \
    #     -t $REMOTE_HOST \
    #     'TEMP_FILE=`mktemp`; cat > $TEMP_FILE; openocd -f board/stm32f4discovery.cfg '${STLINK_SERIAL_ARG}' -c "bindto 0.0.0.0" -c "tcl_port 50001" -c "program $TEMP_FILE verify reset"' \
    #     < $2
fi
