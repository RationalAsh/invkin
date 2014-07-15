#!/usr/bin/python

import serial
import time

ser = serial.Serial('/dev/ttyUSB3', 9600)
count = 0

while True:
    ser.write('1,2,3,4,5,6\n')
    print ser.readline()
    time.sleep(2)
    count += 1
    if(count > 5):
        break

ser.close()
