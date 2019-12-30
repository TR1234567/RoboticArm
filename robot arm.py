#!/usr/bin/env python
# coding: utf-8

# In[63]:


import numpy as np
import cv2
import math
#cam0 10cm = 271pixels
cam0_ratio = 0.03906220198018669
refx = 8.8
refy = -16
refz = -33.5
#cam1 10cm = 272pixels
cam1_ratio = 0.03787851613880087

cap0 = cv2.VideoCapture(0)
cap1 = cv2.VideoCapture(2)

cam0_mtx = np.load("cam0_matrix/cam_mtx.npy")
cam0_dist = np.load("cam0_matrix/dist.npy")
cam0n_mtx = np.load("cam0_matrix/newcam_mtx.npy")
cam0_roi = np.load("cam0_matrix/roi.npy")

cam1_mtx = np.load("cam1_matrix/cam_mtx.npy")
cam1_dist = np.load("cam1_matrix/dist.npy")
cam1n_mtx = np.load("cam1_matrix/newcam_mtx.npy")
cam1_roi = np.load("cam1_matrix/roi.npy")

def mouse_drawing0(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        circles0.append((x, y))
        #print("Left click")
        #print(circles0)
        
        
def mouse_drawing1(event, x, y, flags, params):
    if event == cv2.EVENT_LBUTTONDOWN:
        circles1.append((x, y))
        #print("Left click")
        #print(circles1)
        
        

circles0 = []
circles1 = []
if cap0.isOpened() and cap1.isOpened():
    while(1):
        
        ret0, frame0 = cap0.read()
        ret1, frame1 = cap1.read()
        if ret0 and ret1:
            #out=cv2.transpose(frame0ori)
            #frame0=cv2.flip(out,flipCode=1)
            # undistort
            frame0= cv2.undistort(frame0, cam0_mtx, cam0_dist, None, cam0n_mtx)
            frame1= cv2.undistort(frame1, cam1_mtx, cam1_dist, None, cam1n_mtx)
            
            cv2.imshow("AIM0", frame0)
            cv2.imshow("AIM1", frame1)
            key = cv2.waitKey(30)
            if key == 27:
                break
    cv2.destroyAllWindows()
    
    
    cv2.namedWindow("frame0")
    cv2.setMouseCallback("frame0", mouse_drawing0)
    ret0, frame0 = cap0.read()
    ret1, frame1 = cap1.read()
    if ret0:
        #out=cv2.transpose(frame0ori)
        #frame0=cv2.flip(out,flipCode=1)
        # undistort
        frame0= cv2.undistort(frame0, cam0_mtx, cam0_dist, None, cam0n_mtx)
        
        while(1):
            if len(circles0) == 2:
                pix_distance0U = circles0[0][1]-circles0[1][1]
                print(pix_distance0U)
                pix_distance0V = circles0[0][0]-circles0[1][0]
                print(pix_distance0V)
                cm_distance0Z = pix_distance0U * cam0_ratio
                print(cm_distance0Z)
                cm_distance0Y = pix_distance0V * cam0_ratio
                print(cm_distance0Y)
                targetZ = refz + cm_distance0Z
                print(targetZ)
                targetY = refy + cm_distance0Y
                print(targetY)
                break
            for center_position in circles0:
                cv2.circle(frame0, center_position, 3, (0, 0, 255), -1)
            cv2.imshow("frame0", frame0)
            key = cv2.waitKey(1)
            if key == 27:
                break
    cv2.destroyAllWindows()
    cv2.namedWindow("frame1")
    cv2.setMouseCallback("frame1", mouse_drawing1)
    if ret1:
        frame1= cv2.undistort(frame1, cam1_mtx, cam1_dist, None, cam1n_mtx)
        while(1):
            if len(circles1) == 2:
                pix_distance1U = circles1[0][1]-circles1[1][1]
                print(pix_distance1U)
                pix_distance1V = circles1[0][0]-circles1[1][0]
                print(pix_distance1V)
                cm_distance1Z = pix_distance1U * cam1_ratio
                print(cm_distance1Z)
                cm_distance1X = pix_distance1V * cam1_ratio
                print(cm_distance1X)
                targetZ = refz + cm_distance1Z
                print(targetZ)
                targetX = refx + cm_distance1X
                print(targetX)
                break
            for center_position in circles1:
                cv2.circle(frame1, center_position, 3, (0, 0, 255), -1)
            cv2.imshow("frame1", frame1)
            key = cv2.waitKey(1)
            if key == 27:
                break
    cv2.destroyAllWindows()
    
    
cap0.release()
cap1.release()

# Program to show various ways to read and 
# write data in a file. 
file1 = open("nums1.txt","w") 
L = [str(targetX)+"\n",str(targetY)+"\n",str(targetZ)+"\n"]  
file1.writelines(L) 
file1.close() 


# In[6]:


#control from txt
import serial
import struct
import time
arduino = serial.Serial('COM4', 9600, timeout=.1)
filepath = 'nums2.txt'
with open(filepath) as fp:
    degree3 = int(float(fp.readline().strip()))+90
    degree1 = int(float(fp.readline().strip()))
    degree2 = int(float(fp.readline().strip()))+90

    if degree1 <0:
        degree1 = 0
    if degree1 >130:
        degree1 = 130
    if degree2 <0:
        degree2 = 0
    if degree2 >130:
        degree2 = 130
    if degree3 <80:
        degree3 = 80
    if degree3 >110:
        degree3 = 110
degrees = [degree1,degree2,degree3]  #degree1 degree2 degree3

if degrees[2] > 255:
    degrees_e = [degrees[0],degrees[1],255,degrees[2]-255]
else:
    degrees_e = [degrees[0],degrees[1],degrees[2],0]

# write to arduino as raw binary
#arduino.write(struct.pack('>BBB',15,90,180))
time.sleep(2)
arduino.write(struct.pack('>BBBB',degrees_e[0],degrees_e[1],degrees_e[2],degrees_e[3]))
serialString = arduino.readline()
# Print the contents of the serial data
print(serialString.decode('Ascii'))
#.decode('Ascii')


arduino.close()

