#include <ServoTimer2.h>
boolean toggle1 = 0;
ServoTimer2 myservo1;  // create servo object to control a servo
ServoTimer2 myservo2;

int formmin = 0;
int formmax = 130;
int tomin = 770;
int tomax = 2200;

int target_base_step = map(90,0,360,0,3200);
int current_base_step = map(90,0,360,0,3200);
int step_distance = 0;
int joint1_angle = map(0,formmin,formmax,tomin,tomax);
int joint2_angle = map(90,formmin,formmax,tomin,tomax);

int incoming[4];

int motorSpeed = 1;     //variable to set stepper speed
int motordistance = 195;

//set pin 
int motorPin1 = 8;// Blue   - 28BYJ48 pin 1
int motorPin2 = 9;// Pink   - 28BYJ48 pin 2
int motorPin3 = 10;// Yellow - 28BYJ48 pin 3
int motorPin4 = 11;// Orange - 28BYJ48 pin 4

int servo1 = 5;
int servo2 = 6;

int STEP = 4;
int DIR = 3;

void setup() {

  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);
  myservo1.attach(servo1);
  myservo2.attach(servo2);
  myservo1.write(joint1_angle);
  myservo2.write(joint2_angle);

  
  Serial.begin(9600);

  //set timer1 interrupt at 1Hz
  cli();//stop interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 38;// = ((16*10^6) / (400*1024)) - 1 (must be <65536)  //50 Hz
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
  
  //fint current angle of steppers


  
}
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  if (step_distance > 0)//
  {
    if (toggle1){
      digitalWrite(STEP,HIGH);
      digitalWrite(13,HIGH);
      toggle1 = 0;
    }
    else{
      digitalWrite(STEP,LOW);
      digitalWrite(13,LOW);
      toggle1 = 1;
    }
    step_distance--;
  }
}

void loop(){
  if(Serial.available()>=4) {
    //recive angle
    for (int i = 0; i < 4; i++) {
      incoming[i] = Serial.read();
    }
    if(incoming[0] != -1)
    {
      Serial.print("servo1 :");
      Serial.print(incoming[0]);
      joint1_angle = map(incoming[0],formmin,formmax,tomin,tomax);
      Serial.print(" map :");
      Serial.print(joint1_angle);
    }
    if(incoming[1] != -1)
    {
      Serial.print(" servo2 :");
      Serial.print(incoming[1]);
      joint2_angle = map(incoming[1],formmin,formmax,tomin,tomax);
      Serial.print(" map :");
      Serial.print(joint2_angle);
    }
    if(incoming[2] != -1 && incoming[3] != -1)
    {
      Serial.print(" base :");
      int base = incoming[2]+incoming[3];
      Serial.print(base);
      target_base_step = map(base,0,360,0,3200); //change angle to step count
      Serial.print(" map :");
      Serial.println(target_base_step);
      
    }
    
    //control base angle========================================================================
    if(current_base_step > target_base_step)
    {
      digitalWrite(DIR,HIGH);
      step_distance = current_base_step - target_base_step;
    }
    if(current_base_step < target_base_step)
    {
      digitalWrite(DIR,LOW);
      step_distance = target_base_step - current_base_step ;
    }
    current_base_step = target_base_step;
    
    //control servo=============================================================================
    myservo1.write(joint1_angle);
    myservo2.write(joint2_angle);
    
    //control end===============================================================================
    delay(4000);
    for (int i = 0; i < motordistance; i++)
    {
      counterclockwise();
    }
    delay(2000);
    for (int i = 0; i < motordistance; i++)
    {
      clockwise();
    }
    
    target_base_step = map(90,0,360,0,3200);
    if(current_base_step > target_base_step)
    {
      digitalWrite(DIR,HIGH);
      step_distance = current_base_step - target_base_step;
    }
    if(current_base_step < target_base_step)
    {
      digitalWrite(DIR,LOW);
      step_distance = target_base_step - current_base_step ;
    }
    current_base_step = target_base_step;
    joint1_angle = map(0,formmin,formmax,tomin,tomax);;
    joint2_angle = map(90,formmin,formmax,tomin,tomax);;
    myservo1.write(joint1_angle);
    myservo2.write(joint2_angle);
  }
  

  

  
}
void counterclockwise (){
  // 1
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 5
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  // 6
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  // 7
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  // 8
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
void clockwise(){
  // 1
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 2
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay (motorSpeed);
  // 3
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 4
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 5
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  // 6
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay (motorSpeed);
  // 7
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  // 8
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}
