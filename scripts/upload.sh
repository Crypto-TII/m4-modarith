#!/bin/bash
source select_host_board.sh

USE_OPENOCD=1


if [ $# -ne 1 ]; then
    echo "Usage: $0 <basename of file to upload> # Versions with .bin and .elf extensions must exist"
    exit 1
fi

if [[ -z ${STLINK_SERIAL} ]]
then
    STLINK_SERIAL_ARG=""
else
    STLINK_SERIAL_ARG="--serial ${STLINK_SERIAL}"
fi

if [[ $(st-info --probe) == "Found 0 stlink programmers" ]]
then
    if [[ ${USE_OPENOCD} -eq 1 ]]
    then
        TEMP_FILE_ELF=$(ssh $REMOTE_HOST 'mktemp --suffix=.elf')
        scp $1.elf $REMOTE_HOST:$TEMP_FILE_ELF
        ssh -t $REMOTE_HOST \
            'openocd -f '${BOARD_CFG_FILE}' -c "adapter serial '${STLINK_SERIAL}'" -c "program '$TEMP_FILE_ELF' verify reset exit"'
        RETCODE=$?
        ssh $REMOTE_HOST 'rm '$TEMP_FILE_ELF''
    else
        TEMP_FILE_BIN=$(ssh $REMOTE_HOST 'mktemp --suffix=.bin')
        scp $1.bin $REMOTE_HOST:$TEMP_FILE_BIN
        ssh -t $REMOTE_HOST 'st-flash '${STLINK_SERIAL_ARG}' --reset write '$TEMP_FILE_BIN' 0x08000000'
        RETCODE=$?
        ssh $REMOTE_HOST 'rm '$TEMP_FILE_BIN''
    fi
    exit $RETCODE
else
    if [[ ${USE_OPENOCD} -eq 1 ]]
    then
        openocd -f ${BOARD_CFG_FILE} -c "adapter serial ${STLINK_SERIAL}" -c "program $1.elf verify reset exit"
    else
        st-flash ${STLINK_SERIAL_ARG} --reset write $1.bin 0x08000000
    fi
fi
