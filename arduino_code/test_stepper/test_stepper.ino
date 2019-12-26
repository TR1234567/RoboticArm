int motorPin1 = 8;// Blue   - 28BYJ48 pin 1
int motorPin2 = 9;// Pink   - 28BYJ48 pin 2
int motorPin3 = 10;// Yellow - 28BYJ48 pin 3
int motorPin4 = 11;// Orange - 28BYJ48 pin 4
int motorSpeed = 1;     //variable to set stepper speed
char val = '0';



void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);

  
}



void loop(){

float value = analogRead(A0);

Serial.println((((value-511)*5)/1023)/0.0645);
val = '1';
 if (Serial.available())

  {

    //val = Serial.read();

    //Serial.println(val);

  }

  if (val == '1'){

      clockwise();     

  }

    if (val == '2'){

      counterclockwise();    

  }             

    if (val == '0'){

  digitalWrite(motorPin1, LOW);

  digitalWrite(motorPin2, LOW);

  digitalWrite(motorPin3, LOW);

  digitalWrite(motorPin4, LOW);

  }      

}

 

 

void counterclockwise (){

  // 1
  PORTB &= B00110000;
  PORTB |= B00000001;
  delay(motorSpeed);

  // 2
  PORTB &= B00110000;
  PORTB |= B00000011;
  delay (motorSpeed);

  // 3
  PORTB &= B00110000;
  PORTB |= B00000010;
  delay(motorSpeed);

  // 4
  PORTB &= B00110000;
  PORTB |= B00000110;
  delay(motorSpeed);

  // 5
  PORTB &= B00110000;
  PORTB |= B00000100;
  delay(motorSpeed);

  // 6
  PORTB &= B00110000;
  PORTB |= B00001100;
  delay (motorSpeed);

  // 7
  PORTB &= B00110000;
  PORTB |= B00001000;
  delay(motorSpeed);

  // 8
  PORTB &= B00110000;
  PORTB |= B00001001;
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
