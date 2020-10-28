#!/bin/bash

if [ -z $1 ]; then
    SOURCE_DIR="."
else
    SOURCE_DIR=$1
fi
CM0_IMG=${SOURCE_DIR}/build/cm0.hex
CM4_IMG=${SOURCE_DIR}/build/cm4.hex
OPENOCD_PATH=/Applications/ModusToolbox/tools_2.1/openocd

echo " "
echo "######### Flashing CM0 and CM4  #########"
echo " "
${OPENOCD_PATH}/bin/openocd \
        -s ${OPENOCD_PATH}/scripts \
        -f interface/kitprog3.cfg \
        -f target/psoc6_2m_secure.cfg \
        -c "init; reset init; flash write_image erase ${CM0_IMG}" \
        -c "init; reset init; flash write_image erase ${CM4_IMG}" \
        -c "resume; reset; exit"

echo "######### Done! #########"

