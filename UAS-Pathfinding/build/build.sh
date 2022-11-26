#!/bin/bash 
# ToDo: add checks to install make gcc g++ and other requirments.
#       sudo apt-get install make gcc g++ g++-multilib   
echo "Script to build Pathfinding libraries" 
echo "Building the 32bit Debug Library..." 
cd Debug/x86 
make clean 
make all 
make install 
cd .. 
echo "Building the 64bit Debug Library..." 
cd x64 
make clean 
make all 
make install 
cd .. 
cd .. 
echo "Building the 32bit Release Library..." 
cd Release/x86 
make clean 
make all 
make install 
cd .. 
echo "Building the 64bit Release Library..." 
cd x64 
make clean 
make all 
make install 
echo "Libraries can be found at: ../../../../bin" 
