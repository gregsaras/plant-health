#! /bin/bash

while true
do
cat /dev/ttyACM0|head -n 1 >> sensor_data.txt
sleep 30
done