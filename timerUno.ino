/*
  timerUNO
  ********
  Created by Facundo Daguerre (aka derfaq)
  38ef2d7a-f3a4-11e6-bc64-92361f002671
  GNU GPL
*/

void initTimer1(void){
  //Registros de control del Timer 1
    TCCR1A = 0; // Timer/Counter1 Control Register A, reset
    TCCR1B = 0; // Timer/Counter1 Control Register B, reset
  //Selección del preescaler, 0 = timer detenido ver tabla 16-5
    //TCCR1B |= (1<<CS10);            //1 f: 16 Mhz   t: 62.5ns T(8bits): 16us    f= 62.5 kHz T(16bits): 4.096 ms f=244,14 Hz
    //TCCR1B |= (1<<CS10)|(1<<CS11); //64 f: 250 kHz  t:  4.0us T(8bits): 1.024ms f=976.5 Hz  T(16bits): 262.1 ms f=3.81 Hz
    TCCR1B |= (1<<CS12);             //256 f: 62.5 kHz t: 16.0us T(8bits): 4.096ms f=244.1 Hz  T(16bits): 1.048 s  f=0.95 Hz
    //TCCR1B |= _BV(CS12); es lo mismo, yo no uso el macro _BV, sin embargo es lo mas común
  //Selección de la forma de onda (waveform generation mode) ver tabla 16-4
    //Normal = 0
    //fastPWM 
      //TCCR1A |= (1<<WGM11);
      //TCCR1B |= (1<<WGM13)|(1<<WGM12);
    //Phase and Frequency Correct
      TCCR1B |= (1<<WGM13);
  //Selección de las salidas comparadas (compare output mode) ver tablas 16-1,-2,-3
    //OC1A = Pin 9
      TCCR1A |= (1<<COM1A1); //Clear in compare match
      //TCCR1A |= (1<<COM1A1)|(1<<COM1A0); //Set in compare match
    //OC1A = Pin 10
      //TCCR1A |= (1<<COM1B1); //Clear in compare match
      TCCR1A |= (1<<COM1B1)|(1<<COM1B0); //Set in compare match
  //Seteo de frecuencia y ciclo de trabajo
    ICR1 = 62536; //ICR1 = 8190; ICR1 = 8324
    OCR1A = (ICR1>>1);
    OCR1B = OCR1A;
}


void enableOutput(){
  //AVR style
    DDRB |= (1<<PB1)|(1<<PB2);
  //Arduino style
    //pinMode(9,OUTPUT);
    //pinMode(10,OUTPUT);
}

void setup(){
  initTimer1();
  enableOutput();
}

void loop(){
  ;
}
