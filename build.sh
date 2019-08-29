#!/bin/bash

#===  FUNCTION  ================================================================
#         NAME:  usage
#  DESCRIPTION:  Display usage information.
#===============================================================================
function usage ()
{
    echo "Usage :  $0 [options] [--]"
    echo ""
    echo "Options:"
    echo "  -h|help       Display this message"
    echo "  -d|debug      Build with debug enabled"
    echo "  -i|install    Install binary after building"

}    # ----------  end of function usage  ----------

#-----------------------------------------------------------------------
#  Handle command line arguments
#-----------------------------------------------------------------------

while [ "$#" -gt 0 ]; do
    case "$1" in
        -h|help )
            usage;
            exit 0;;
        -d|debug )
            CMAKE_BUILD_FLAG="-DCMAKE_BUILD_TYPE=Debug";
            shift;;
        -i|install )
            INSTALL_BIN=1;
            shift;;
        -* )
            echo -e "\nOption does not exist: $1\n";
            usage;
            exit 1;;
        * )
            echo -e "\nOption does not exist: $1\n";
            usage;
            exit 1;;
    esac
done

#-----------------------------------------------------------------------
# Build binary
#-----------------------------------------------------------------------

BUILD_DIR=build

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
fi

cd "$BUILD_DIR" && cmake $CMAKE_BUILD_FLAG .. && make

if [ ! -z "$INSTALL_BIN" ]; then
    if [ ! "$(id -u)" -eq  0 ]; then
        echo "You must be root to install this binary!"
        exit 1
    fi

    make install
fi

exit 0
