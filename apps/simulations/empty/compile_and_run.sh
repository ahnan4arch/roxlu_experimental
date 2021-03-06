#!/bin/sh

d=${PWD}
app=${PWD##*/}

if [ ! -d build ] ; then
   mkdir build
fi

if [ ! -d bin ] ; then 
   mkdir bin
   mkdir bin/data
fi

cd build
cmake ../
make install
cd ${d}
cd bin
./${app}