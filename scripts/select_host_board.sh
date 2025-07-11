#!/bin/bashsh

REMOTE_HOST=<hostname>

BOARD=$(grep BOARD ../build/CMakeCache.txt | sed -e 's/.*=//')

if [ $BOARD = "STM32F4DISCOVERY" ]
then
    STLINK_SERIAL=<serial_number>
    CLOCK_FREQUENCY_BENCHMARK=24
    CLOCK_FREQUENCY_FAST=168
    BOARD_CFG_FILE=board/stm32f4discovery.cfg
elif [ $BOARD = "NUCLEO-L4R5ZI" ]
then
    STLINK_SERIAL=<serial_number>
    CLOCK_FREQUENCY_BENCHMARK=20
    CLOCK_FREQUENCY_FAST=120
    BOARD_CFG_FILE=board/st_nucleo_l4r5zi.cfg
else
    echo "Invalid development board in CMakeCache.txt"
    exit 1
fi

echo Running on host $REMOTE_HOST, selected board $BOARD with serial number $STLINK_SERIAL
