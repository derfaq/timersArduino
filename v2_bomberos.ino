#include <Button.h>

/*
 * Bomberos
 */

/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 11}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//--->end of keypad initialization

// DTMF (Dual Tone Multiple Frequency) Demonstration

// http://en.wikipedia.org/wiki/Dual-tone_multi-frequency

// To mix the output of the signals to output to a small speaker (i.e. 8 Ohms or higher),
// simply use 1K Ohm resistors from each output pin and tie them together at the speaker.
// Don't forget to connect the other side of the speaker to ground!

#include <Tone.h>

Tone freq1;
Tone freq2;

/*
        1209 Hz 1336 Hz 1477 Hz 1633 Hz
697  Hz    1       2       3       A
770  Hz    4       5       6       B
852  Hz    7       8       9       C
941  Hz    *       0       #       D
*/
//                            0,    1,    2,    3,    4,    5,    6,    7,   8,     9,*(10),#(12)
const int DTMF_freq1[] = { 1336, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1336, 1477, 1209, 1477};
const int DTMF_freq2[] = {  941,  697,  697,  697,  770,  770,  770,  852,  852,  852,  941,  941};
const int duration = 200;

void playDTMF(uint8_t number, long duration)
{
  freq1.play(DTMF_freq1[number], duration);
  freq2.play(DTMF_freq2[number], duration);  
}
//--->end of tone initialization

/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A5, A4); // RX, TX

//--->end of serial intialization

/*
||
|| @file Button.pde
|| @version 1.1
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Display the intuitive way of using a button when using this Hardware Abstraction class
|| #
||
|| @license
|| | Copyright (c) 2009 Alexander Brevig. All rights reserved.
|| | This code is subject to AlphaLicence.txt
|| | alphabeta.alexanderbrevig.com/AlphaLicense.txt
|| #
||
*/

#include <Button.h>

//create a Button object at pin 12
/*
|| Wiring:
|| GND -----/ ------ pin 12
*/
Button tubo = Button(2,INPUT_PULLUP);

//--->end of button initialization

#define LED 4

void setup(){
  Serial.begin(9600);

  freq1.begin(3);
  freq2.begin(10);

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);

  pinMode(LED,OUTPUT);

}

void ring(){
  digitalWrite(LED,HIGH);
  //Sirena
  do {
    for (int i = 0; i<4;i++) { 
     freq1.play(1395);
     delay(50);
     freq1.stop();
     freq2.play(653);
     delay(50);
     freq2.stop();
    }
    delay(100);
    for (int i = 0; i<4;i++) { 
     freq1.play(1395);
     delay(50);
     freq1.stop();
     freq2.play(653);
     delay(50);
     freq2.stop();
    }
    freq1.stop();
    freq2.stop();
    delay(800);
  }while(tubo.isPressed());
  //Cuando atiendo
  digitalWrite(LED,LOW);
  freq1.stop();
  freq2.stop();  
}
  

void loop(){
  if(tubo.isPressed()){
      digitalWrite(LED,LOW);
      if(mySerial.find("100")){
      ring();
      }
  }else{
      digitalWrite(LED,HIGH);
      char customKey = customKeypad.getKey();
      
      switch(customKey){
        case '0': playDTMF(0, duration); mySerial.write(customKey); break;
        case '1': playDTMF(1, duration); mySerial.write(customKey); break;
        case '2': playDTMF(2, duration); mySerial.write(customKey); break;
        case '3': playDTMF(3, duration); mySerial.write(customKey); break;
        case '4': playDTMF(4, duration); mySerial.write(customKey); break;
        case '5': playDTMF(5, duration); mySerial.write(customKey); break;
        case '6': playDTMF(6, duration); mySerial.write(customKey); break;
        case '7': playDTMF(7, duration); mySerial.write(customKey); break;
        case '8': playDTMF(8, duration); mySerial.write(customKey); break;
        case '9': playDTMF(9, duration); mySerial.write(customKey); break;
        case '*': playDTMF(10, duration); mySerial.write(customKey); break;
        case '#': playDTMF(11, duration); mySerial.write(customKey); break;
        default: break;
      }
  }
  
}
