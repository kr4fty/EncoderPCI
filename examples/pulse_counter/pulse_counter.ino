/*
 * Pulse COunter
 *    Autor: Tapia Favio
 *    
 * The program is very simple, it rotates for 1 second in one direction and 
 * after that time the encoder position change is shown. Then change the 
 * direction of rotation, turn for a second and again shows the change of 
 * direction.  
 * 
 * An dc motor with an encoder coupled to the shaft was used.
 * The hardware used is an H-bridge type L293. In addition the used pins were:
 *      For the motor the following outputs: 6,5,10 (IN1, IN2 and PWM)
 *      For the encoder the following inputs: A2, A3 (INA and INB)
 *      
 */

#define LIBCALL_ENABLEINTERRUPT
#include <EncoderPCI.h>
#include "motor.h"

Encoder myEnc= Encoder(inA, inB);

double actualPosition;
double oldPos;

void setup()
{
  noInterrupts();
  
  pinMode(pwm, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  #ifdef PWM31KHZ
    TCCR1B = TCCR1B & 0b11111000 | 1; // set 31Kh
  #endif

  Serial.begin(9600);
  interrupts();
  myEnc.write(0);
  delay(500);
}

void loop()
{
  motorStop();
  if(direction)
    turnClockwise();
  else
    turnCounterClockwise();

  delay(1000);
  
  direction?direction=0:direction=1;
  
  actualPosition= myEnc.read();
  if(oldPos!=actualPosition){
    Serial.println(actualPosition);
    oldPos = actualPosition;
  }
  
  myEnc.write(0);
}
