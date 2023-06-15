#include <limitS.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


#define stepPin 4
#define dirPin 8
#define Enable 11
// #define limitL 2
// #define limitR 3

#define solenoide 12


int time=500;
int switchL_Value=1;
int switchR_Value=1;



int appValue;

//constructor del bluetooth
SoftwareSerial miBT(5,9);//tx,rx del bluetooth
limitS limitL(2);
limitS limitR(3);

void limitInterrumptL(){
  if (limitL.value()==0)
  {
    digitalWrite(Enable,HIGH);
    switchL_Value=0;
  }
  else{
    switchL_Value=1;
  }
}
void limitInterrumptR(){
  if (limitR.value()==0)
  {
    digitalWrite(Enable,HIGH);
    switchR_Value=0;
  }
  else{
    switchR_Value=1;
  }
}


void setup (){
  //Pines motor
    pinMode(dirPin,OUTPUT);
    pinMode(stepPin,OUTPUT);
    pinMode(Enable,OUTPUT);
    
  //Pin Solenoide
    pinMode(solenoide,OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(2),limitInterrumptL,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),limitInterrumptR,CHANGE);
  Serial.begin(9600);
  miBT.begin(38400);
}



void loop(){
 
  

  if (miBT.available())
  {
    appValue=miBT.read();
    if (appValue==80)
    {
      digitalWrite(solenoide,HIGH);
    }
    else{
      digitalWrite(solenoide,LOW);
    }
    if ((appValue==76)&&(switchR_Value==1))
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,HIGH);
      // Serial.println("a");
      while (appValue!=65){//83 significa stop
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        appValue=miBT.read();
        if (appValue==80)
        {
          digitalWrite(solenoide,HIGH);
        }
        else if(appValue==83){
          digitalWrite(solenoide,LOW);
        }
      }
    }
    else if ((appValue==82)&&(switchL_Value==1))
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,LOW);
      while (((appValue!=65))&&(switchL_Value==1)){//83 significa stop
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        appValue=miBT.read();
        if (appValue==80)
        {
          digitalWrite(solenoide,HIGH);
        }
        else if(appValue==83){
          digitalWrite(solenoide,LOW);
        }
      }
    }
    else{
      digitalWrite(Enable,HIGH);
      digitalWrite(stepPin, LOW);
    }
  }
  else{
    digitalWrite(Enable,HIGH);

  }
}

