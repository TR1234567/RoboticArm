#include <ServoTimer2.h>
ServoTimer2 myservo1;  // create servo object to control a servo
ServoTimer2 myservo2;
int servo1 = 5;
int servo2 = 6;
int degree = 2200; //90 = 1450 30 = 770 155 = 2200
void setup() {
  // put your setup code here, to run once:
  myservo1.attach(servo1);
  myservo2.attach(servo2);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo1.write(degree);
  myservo2.write(1450);
  delay(500);
}
