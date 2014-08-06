#include <Ultrasonic.h>

int enMotDir = 9; //pwm
int enMotEsq = 10;
int motDir2 = 3;
int motDir7 = 4;
int motEsq15 = 6;
int motEsq10 = 5;
const int vel = 180;
const int velGiro = 200;

#define ECHO 12
#define TRIGGER  13

int distancia = 0;
long microSec = 0;

Ultrasonic sensorUltrasonico(TRIGGER,ECHO);

void setup(){

  pinMode(enMotDir,OUTPUT);
  pinMode(enMotEsq,OUTPUT);
  pinMode(motDir2,OUTPUT);
  pinMode(motDir7,OUTPUT);
  pinMode(motEsq15,OUTPUT);
  pinMode(motEsq10,OUTPUT);
  Serial.begin(9600);
}


void loop(){
  microSec = sensorUltrasonico.timing();
  distancia = sensorUltrasonico.convert(microSec, Ultrasonic::CM);
  
  Serial.println(distancia);
  
  if(distancia <2){
    distancia =6;
  }
  if(distancia >= 15){
    digitalWrite(2, HIGH);  
    frente();
    delay(100);  
  }
  if (distancia < 15 )
  {      
   digitalWrite(2, LOW);
   parado();
   delay(3000);
  }  

 // mudaDirecao();
}

void frente(){
  digitalWrite(motDir2, HIGH);
  digitalWrite(motDir7, LOW);
    
  digitalWrite(motEsq10, LOW);
  digitalWrite(motEsq15, HIGH);
  
  analogWrite(enMotDir, vel+10); 
  analogWrite(enMotEsq, vel-10);
}

void tras(){
  digitalWrite(motDir2, LOW);
  digitalWrite(motDir7, HIGH);
   
  digitalWrite(motEsq10, HIGH);
  digitalWrite(motEsq15, LOW);
  
  analogWrite(enMotDir, vel);
  analogWrite(enMotEsq, vel);
}

void esquerda(){
  digitalWrite(motDir2, LOW);
  digitalWrite(motDir7, HIGH);
  
  digitalWrite(motEsq10, LOW);
  digitalWrite(motEsq15, HIGH);
  
  analogWrite(enMotDir, velGiro);
  analogWrite(enMotEsq, velGiro);
}

void direita (){
 
  digitalWrite(motEsq10, HIGH);
  digitalWrite(motEsq15, LOW);
  
  digitalWrite(motEsq10, HIGH);
  digitalWrite(motEsq15, LOW);
  
  analogWrite(enMotEsq, vel); 
  analogWrite(enMotEsq, vel);
}

void mudaDirecao(){
  tras();
  delay(1000);
  esquerda();
  delay(580);
}
void parado(){
  digitalWrite(motDir2, LOW);
  digitalWrite(motDir7, LOW);
    
  digitalWrite(motEsq10, LOW);
  digitalWrite(motEsq15, LOW);
  
  analogWrite(enMotDir, 0); 
  analogWrite(enMotEsq, 0);
}
