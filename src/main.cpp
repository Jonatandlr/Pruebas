#include <Arduino.h>
#include <joystick.h>
#include <limitS.h>
// #include <Stepper.h>



int dirPin=2;
int stepPin=3;
int time=2000;
int Svalue;

String JoyValue;

limitS Switches(4,5);
joystick joy(A0);

void setup(){
  joy.setup();
  Switches.setup();
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  
    JoyValue=joy.direction();
    Svalue=Switches.value();
    
    Serial.println(Svalue);

    if ((JoyValue=="RIGHT")&& (Svalue==0))
    {
      digitalWrite(dirPin,HIGH);
      while ((JoyValue=="RIGHT")&& (Svalue==0))
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        JoyValue=joy.direction();
        Svalue=Switches.value();
      }
    }
    else if ((JoyValue=="LEFT")&& (Svalue==0))
    {
      digitalWrite(dirPin,LOW);
      while ((JoyValue=="LEFT")&& (Svalue==0))
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        JoyValue=joy.direction();
        Svalue=Switches.value();
      }
    }
}