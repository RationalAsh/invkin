#!/usr/bin/python

import time
import serial
import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 31415

ser = serial.Serial('/dev/ttyACM1', 9600)
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(10)
    print "Recieved message: ", data
    if(data == 'exit'):
        break
    if(data == 'L'):
        ser.write('l\n')
        print "Going Left!"
    if(data == 'R'):
        ser.write('r\n');
        print "Going right!"
    if(data == 'S'):
        ser.write('h\n')
        print "Stopping!"

ser.close()

