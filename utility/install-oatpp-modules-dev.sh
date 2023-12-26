#!/bin/sh

BUILD_TYPE=$1

if [ -z "$BUILD_TYPE" ]; then
    BUILD_TYPE="Debug"
fi

rm -rf oatpp

mkdir oatpp
cd oatpp

##########################################################
## install oatpp module

function install_module () {

BUILD_TYPE=$1
MODULE_NAME=$2
NPROC=$(nproc)

if [ -z "$NPROC" ] || [ -z "$MAKE_PARALLEL_EXECUTION" ] || [ "$MAKE_PARALLEL_EXECUTION" = "OFF" ]
then
    NPROC=1
elif [ $NPROC > 2 ] || [ "$MAKE_PARALLEL_EXECUTION" = "ON" ]
then
    echo "MAKE_PARALLEL_EXECUTION"
    echo $MAKE_PARALLEL_EXECUTION
    NPROC="$(($NPROC-2))"
fi

echo "\n\nINSTALLING MODULE '$MODULE_NAME' ($BUILD_TYPE) using $NPROC threads ...\n\n"

git clone --depth=1 https://github.com/oatpp/$MODULE_NAME

cd $MODULE_NAME
mkdir build
cd build

cmake -DOATPP_DISABLE_ENV_OBJECT_COUNTERS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOATPP_BUILD_TESTS=OFF ..
make install -j $NPROC

cd ../../

}

##########################################################

install_module $BUILD_TYPE oatpp
install_module $BUILD_TYPE oatpp-curl

cd ../
