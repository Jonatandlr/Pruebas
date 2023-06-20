#include <limitS.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


//definir pines 
#define stepPin 4
#define dirPin 8
#define Enable 11
#define solenoide 12

//variables
int time=450;
int switchL_Value=1;
int switchR_Value=1;
int appValue;

//constructor del bluetooth
SoftwareSerial miBT(5,9);//TXD, RXD del bluetooth

//constructor LimitSwitches
limitS limitL(2);
limitS limitR(3);

//Funciones de Interrumpcion
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

  //Declaracion de funciones de interrumpcion
    attachInterrupt(digitalPinToInterrupt(2),limitInterrumptL,CHANGE);
    attachInterrupt(digitalPinToInterrupt(3),limitInterrumptR,CHANGE);

  Serial.begin(9600);
  miBT.begin(38400);
}



void loop(){
  if (miBT.available()) 
  {
    
    appValue=miBT.read();//Le el valor de la aplicacion en ASCII(L(76),R(82),A(65),P(80) o S(83))

    if (appValue==80)//actuva o desactiva el solenoide
    {
      digitalWrite(solenoide,HIGH);
    }
    else{
      digitalWrite(solenoide,LOW);
    }

    if ((appValue==76)&&(switchR_Value==1))//activa el nema a la izquierda
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,HIGH);
      while (appValue!=65){
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
    else if ((appValue==82)&&(switchL_Value==1))//actuva el nema a la derecha 
    {
      digitalWrite(Enable,LOW);
      digitalWrite(dirPin,LOW);
      while (((appValue!=65))&&(switchL_Value==1)){//65 es A valor que se recibe cuando se deja de precionar deracha o izquierda
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
    }
  }
  else{
    digitalWrite(Enable,HIGH);
  }
}

