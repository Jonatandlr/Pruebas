
#include <Arduino.h>
#include <joystick.h>
#include <limitS.h>
// #include <Stepper.h>



int dirPin=2;
int stepPin=3;
int time=500;
int joyValue;
int SwitchesValue;
// int stepsPerRevolution = 200;


// String JoyValue;
joystick joy(A0);
limitS limitR(6);
limitS limitL(7);

void setup (){
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
  joy.setup();
  Serial.begin(9600);
}


void loop(){
  SwitchesValue=limitL.interrupt(limitL.value(),limitR.value());
  joyValue=joy.valor();
  if ((joyValue>=1000)&&(SwitchesValue==1))
  {
    digitalWrite(dirPin,HIGH);
    while ((joyValue>=1000)&&(SwitchesValue==1)){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(time);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(time);
      joyValue=joy.valor();
      SwitchesValue=limitL.interrupt(limitL.value(),limitR.value());
      // Serial.println(joyValue);
    }
  }
  else if ((joyValue<=300)&&(SwitchesValue==1))
  {
    digitalWrite(dirPin,LOW);
    while ((joyValue<=300)&&(SwitchesValue==1)){
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(time);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(time);
      joyValue=joy.valor();
      SwitchesValue=limitL.interrupt(limitL.value(),limitR.value());
      // Serial.println(joyValue);
    }
  }
}
  
