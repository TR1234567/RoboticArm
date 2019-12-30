from time import sleep
import serial
import struct

myfile = open("nums2.txt", "rt") # open lorem.txt for reading text
contents1 = myfile.readlines(1)   
contents2 = myfile.readlines(2) 
contents3 = myfile.readlines(3)
myfile.close()                   # close the file
j1s=contents1[0].rstrip()                 # print contents
j2s=contents2[0].rstrip()  
j3s=contents3[0].rstrip()
j1f=float(j1s)
j2f=float(j2s)
j3f=float(j3s)
j1=int(180.00-j1f)
j2=int(j2f)
j3=int(j3f)

ser = serial.Serial('COM5', 9600,timeout=1)
sleep(3) 

while True:
    ser.write(struct.pack('>bbb',j1,j2,j3))

