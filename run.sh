#! /bin/bash

BUILD_DIR="build"

if [ ! -d $BUILD_DIR ]
then 
    ./build.sh
    ./$BUILD_DIR/bin/cardproj $1
else
    ./$BUILD_DIR/bin/cardproj $1
fi 