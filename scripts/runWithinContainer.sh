#!/bin/bash

# 
#    A bash script used with Docker for compiling The Ev3dev C++ Wrapper Library
#
#    Copyright (c) 2021, 2022 - Eisverygoodletter
#
#    This file is part of The Ev3dev C++ Wrapper Library.
#    The Ev3dev C++ Wrapper Library is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by the Free Software Foundation, 
#    either version 3 of the License, or (at your option) any later version.
#    The Ev3dev C++ Wrapper Library is distributed in the hope that it will be useful, 
#    but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
#    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
#    You should have received a copy of the GNU General Public License 
#    along with The Ev3dev C++ Wrapper Library. If not, see <https://www.gnu.org/licenses/>.
echo -e "\e[1;37m"

# processing flags -----------------------------------------------------------------------

# flag "-n" indicates that a new file has been added and reconfiguration is required
# clock skew detected may be a side effect but should not be a problem
newFile=false

# flag "-w" indicates that the bin folder should be wiped and subsequently rebuilt
# the "-n" flag will be used if the "-w" flag is used
wipeBin=false

# flag "-v" indicates the verbosity (whether if it will check the file size or not)
# making it verbose may make the build slower
verbose=false

optimizationLevel="-Os"

while getopts 'nwO:v' flag; do
  case "${flag}" in
    n) newFile=true ;;
    w) wipeBin=true
        newFile=true ;;
    O) optimizationLevel="-O${OPTARG}"
        newFile=true ;;
    v) verbose=true 
        newFile=true ;;
    *) echo "UNKNOWN FLAG ${flag}"
       exit 1 ;;
  esac
done

rebuildDetails="
-------- REBUILD DETAILS ----------
optimization Level: ${optimizationLevel}
verbosity         : ${verbose}
"
if [ $newFile = false ]; then
    rebuildDetails=""
fi

echo "
Build configuration details ----------------------------------------------------------------
------- GLOBAL DETAILS -----------
Reconfigure files : ${newFile}
Wipe bin folder   : ${wipeBin}
${rebuildDetails}
Commands used     : $@
--------------------------------------------------------------------------------------
"
if [ $wipeBin = true ]; then
    echo "Wiping bin folder"
    sudo rm -rf bin
fi
if [ $newFile = true ]; then
    echo "Reconfiguring cmake files"
    cmake ./ \
        -G"Unix Makefiles" \
        -B"bin" \
        -DOPTIMIZATION_LEVEL=${optimizationLevel} \
        -DVERBOSE=${verbose}
fi

echo "building library starting with $(nproc) jobs"

cmake --build bin -j $(nproc)