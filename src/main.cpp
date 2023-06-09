
#include <Arduino.h>
#include <joystick.h>
#include <limitS.h>
#include <SoftwareSerial.h>

// #include <Stepper.h>



#define stepPin 3
#define dirPin 2
#define Enable 11


int time=900;
// int joyValue;

int switchL_Value;
int switchR_Value;

int appValue=0;


// String JoyValue;
joystick joy(A0);//construictor del joystick
//constructores de los limits
limitS limitR(6);
limitS limitL(7);

//constructor del bluetooth
SoftwareSerial miBT(5,9);//tx,rx

void setup (){
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
  joy.setup();

  Serial.begin(9600);
  miBT.begin(38400);
}


void loop(){
  

  if (miBT.available())
  {
    appValue=miBT.read();

    switchR_Value=limitR.value();
    switchL_Value=limitL.value();

    //giro Derecha 
    if ((appValue==82)&&(switchR_Value==1))//el 82 es la letra R en ascii de Right
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,HIGH);
      while ((appValue!=83)&&(switchR_Value==1)){//83 significa stop
        digitalWrite(stepPin, HIGH);
        // delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        switchR_Value=limitR.value();
        appValue=miBT.read();
        // Serial.println(joyValue);
      }
    }

    else if ((appValue==76)&&(switchL_Value==1))//el 76 es la letra L en ascii de Left
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,LOW);
      while ((appValue!=83)&&(switchL_Value==1)){//83 significa stop
        digitalWrite(stepPin, HIGH);
        // delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        appValue=miBT.read();
        switchL_Value=limitL.value();
        // Serial.println(joyValue);
      }
    }
    else{
      digitalWrite(Enable,HIGH);
    }
  }
  
}
  
