#include <Servo.h>
int incoming[4];
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(5);
}

void loop(){
  if(Serial.available()>=4) {
      for (int i = 0; i < 4; i++) {
        incoming[i] = Serial.read();
      }
      if(incoming[0] != -1)
      {
        Serial.print("output :");
        Serial.println(incoming[0]);
      }
      if(incoming[1] != -1)
      {
        Serial.println(incoming[1]);
      }
      if(incoming[2] != -1 && incoming[3] != -1)
      {
        int base = incoming[2]+incoming[3];
        Serial.println(base);
      }

    }
    myservo.write(incoming[0]);
    


}
