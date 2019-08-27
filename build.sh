#!/bin/bash

#===  FUNCTION  ================================================================
#         NAME:  usage
#  DESCRIPTION:  Display usage information.
#===============================================================================
function usage ()
{
    echo "Usage :  $0 [options] [--]

    Options:
    -h|help       Display this message
    -d|debug      Build with debug enabled"

}    # ----------  end of function usage  ----------

#-----------------------------------------------------------------------
#  Handle command line arguments
#-----------------------------------------------------------------------

while getopts ":hd" opt
do
    case $opt in
        h|help )
            usage;
            exit 0
            ;;
        d|debug )
            CMAKE_BUILD_FLAG="-DCMAKE_BUILD_TYPE=Debug"
            ;;
        * )
            echo -e "\n  Option does not exist : $OPTARG\n"
            usage;
            exit 1
            ;;
    esac
done
shift $(($OPTIND-1))

#-----------------------------------------------------------------------
# Build binary
#-----------------------------------------------------------------------

BUILD_DIR=build

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" && cmake $CMAKE_BUILD_FLAG .. && make
