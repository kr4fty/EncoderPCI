#ifndef _MOTOR_H
#define _MOTOR_H

#define PWM31KHZ    // Habilito la salida de pwm a 31.25 KHz

#define pwm 10 // Habilito/Desabilito, chip enable, del L293D
#define in1  6 // Salida hacia el pin 2, IN1, del L293D
#define in2  5 // Salida hacia el pin 7, IN2, del L293D
#define inA A2 // Encoder INA pin
#define inB A3 // Encoder INB pin 

#define SPEED 150 //  

bool direction;  //0:left 1:right

 void motorStop(){
  analogWrite(pwm, 0);
 }
 void fastMotorStop(){
  digitalWrite(pwm, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
 }
 void turnClockwise(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(pwm, SPEED);
 }
 void turnCounterClockwise(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(pwm, SPEED);
 }

#endif

