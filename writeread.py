import serial

##ser = serial.Serial('COM5', 115200)
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
j1=int(180-j1f)
print(j1)
j2=int(j2f)
print(j2)
j3=int(j3f)
print(j3)
j1b= bytes(j1)
print(j1b)
j2b= bytes(j2)
print(j2b)
j3b= bytes(j3)
print(j3b)
'''if(ser.isOpen()):
    ser.write(j1b)
    ser.write(j2b)
    ser.write(j3b)'''