boolean toggle1 = 0;

int target_base_step1 = 0;
int current_base_step1 = 0; 
int step_distance1 = 0;

int target_base_step2 = 0;
int current_base_step2 = 0; 
int step_distance2 = 0;

int STEP1 = 4;
int DIR1 = 3;
int STEP2 = 6;
int DIR2 = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(STEP1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(DIR2, OUTPUT);

  //set timer1 interrupt
  cli();//stop interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 38;// = ((16*10^6) / (frequency*1024)) - 1 (must be <65536)  //ตั้งความถี่ 400 Hz
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
  
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  if (toggle1)
  {
    if (step_distance1 > 0)
    {
      digitalWrite(STEP1,HIGH);
      step_distance1--;
    }
    if (step_distance2 > 0)
    {
      digitalWrite(STEP2,HIGH);
      step_distance2--;
    }
    toggle1 = 0;
  }
  else
  {
    if (step_distance1 > 0)
    {
      digitalWrite(STEP1,LOW);
      step_distance1--;
    }
    if (step_distance2 > 0)
    {
      digitalWrite(STEP2,LOW);
      step_distance2--;
    }
    toggle1 = 1;
  }
}

void loop() {

  //ใส่ target step เดี๋ยวมันวิ่งไปเอง
  
  //stepper1
  if(current_base_step1 > target_base_step1)
  {
    digitalWrite(DIR1,HIGH);
    step_distance1 = current_base_step1 - target_base_step1;
  }
  if(current_base_step1 < target_base_step1)
  {
    digitalWrite(DIR1,LOW);
    step_distance1 = target_base_step1 - current_base_step1 ;
  }
  current_base_step1 = target_base_step1;

  //stepper2
  if(current_base_step2 > target_base_step2)
  {
    digitalWrite(DIR2,HIGH);
    step_distance2 = current_base_step2 - target_base_step2;
  }
  if(current_base_step2 < target_base_step2)
  {
    digitalWrite(DIR2,LOW);
    step_distance2 = target_base_step2 - current_base_step2 ;
  }
  current_base_step2 = target_base_step2;

}
