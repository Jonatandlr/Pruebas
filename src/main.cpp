
#include <Arduino.h>
#include <limitS.h>
#include <SoftwareSerial.h>


#define stepPin 3
#define dirPin 8
#define Enable 11
#define pinI 2
#define solenoide 12


int time=400;
int joyValue;
int switchL_Value;
int switchR_Value;


int appValue=0;
volatile boolean irs=false;



//constructores de los limits
limitS limitR(6);
limitS limitL(7);

//constructor del bluetooth
SoftwareSerial miBT(5,9);//tx,rx del bluetooth


void buttonInterrumpt(){  
  Serial.println("INTERRUMPT");
  if (irs)
  {
    irs=false;
    digitalWrite(solenoide,LOW);
    Serial.println("apagado");
  }
  else{
    irs=true;
    digitalWrite(solenoide,HIGH);
    Serial.println("prendido");
    
  }
}


void setup (){
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
  pinMode(pinI,OUTPUT);
  pinMode(solenoide,OUTPUT);

  

  attachInterrupt(digitalPinToInterrupt(pinI), buttonInterrumpt,CHANGE);
  Serial.begin(9600);
  miBT.begin(38400);
}



void loop(){

  //solenoide 
  // if (miBT.available())
  // {
  //   Serial.println("IF");
  //   /* code */
  //   appValue=miBT.read();
  //   if (appValue==80){
  //     digitalWrite(pinI,HIGH);
  //   }
  //   else if (appValue==83)
  //   {
  //     digitalWrite(pinI,LOW);
  //   }
  // }
    
  if (miBT.available())
  {
    appValue=miBT.read();
    switchR_Value=limitR.value();
    switchL_Value=limitL.value();
    //Giro Derecha 
    if ((appValue==82)&&(switchR_Value==1))//El 82 es la letra R en ascii de Right
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,HIGH);
      while ((appValue!=83)&&(switchR_Value==1)){//83 significa stop
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        switchR_Value=limitR.value();
        appValue=miBT.read();
        if (appValue==80){
          digitalWrite(pinI,HIGH);}
        else if (appValue==83){
          digitalWrite(pinI,LOW);}
      }
    }

    else if ((appValue==76)&&(switchL_Value==1))//El 76 es la letra L en ascii de Left
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,LOW);
      while ((appValue!=83)&&(switchL_Value==1)){//83 significa stop
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(time);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(time);
        appValue=miBT.read();
        switchL_Value=limitL.value();
        if (appValue==80){
          digitalWrite(pinI,HIGH);}
        else if (appValue==83){
          digitalWrite(pinI,LOW);}

      }
    }
    else{
      digitalWrite(Enable,HIGH);
      appValue=miBT.read();
      if (appValue==80){
          digitalWrite(pinI,HIGH);}
      else if (appValue==83){
        digitalWrite(pinI,LOW);}
    }
  }
}

