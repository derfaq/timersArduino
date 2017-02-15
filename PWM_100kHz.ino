/*
  PWM_100kHz
  **********
  Created by Facundo Daguerre (aka derfaq)
  38ef2d7a-f3a4-11e6-bc64-92361f002671
  GNU GPL
*/

void initTimer1(void){
  TCCR1A = 0; // Timer/Counter1 Control Register A, reset
  TCCR1B = 0; // Timer/Counter1 Control Register B, reset
  TCCR1A = (1<<WGM11)|(1<<COM1A1)|(1<<COM1B1)|(1<<COM1B0); //OutPut
  TCCR1B |= (1<<CS10); //64
  TCCR1B |= (1<<WGM13)|(1<<WGM12); //FastPWM
  ICR1 = 159; //100Kz
  OCR1A = (ICR1>>1);
  OCR1B = OCR1A;
}

void enableOutput(){
  DDRB |= (1<<1)|(1<<2);
}

void setup(){
  initTimer1();
  enableOutput();
}

void loop(){
  ;
}
