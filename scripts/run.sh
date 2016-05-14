#!/bin/bash

#get parameter file name
paramFileName=$1

#run simulator in the background
cd ..
./wave_simulate.tsk -p $paramFileName -o sample/out > /dev/null &

sleep 5

#run movie builder
cd scripts
python wave.py ../$paramFileName ../sample/out
