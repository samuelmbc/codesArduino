#include <Ultrasonic.h> //importa a biblioteca do sensor Ultrasonico 

int enMotDir = 9;  //Controle por PWM velocidade do motor direita
int enMotEsq = 10; //Controle por PWM velocidade do motor esquerda
int motDir2 = 3;   //Sinal motor direita ligado no pino 2 do L293D
int motDir7 = 4;   //Sinal motor direita ligado no pino 7 do L293D
int motEsq15 = 6;  //Sinal motor esquerda ligado no pino 5 do L293D
int motEsq10 = 5;  //Sinal motor esquerda ligado no pino 10 do L293D
const int vel = 180;//para controlar a velocida de frente e traz do robo
const int velGiro = 200;//para controlar a velocida giro do robo
int distancia = 0; //variável que irá receber os valores da distância 
long microSec = 0; //variavel exigida para conversão de valores de distância

#define ECHO 12 //dinição de variavel para o sensor de distância 
#define TRIGGER  13 //dinição de variavel para o sensor de distância

Ultrasonic sensorUltrasonico(TRIGGER,ECHO); //chamada do metodo do sensor ultrasonico

void setup(){
  pinMode(enMotDir,OUTPUT);
  pinMode(enMotEsq,OUTPUT);
  pinMode(motDir2,OUTPUT);
  pinMode(motDir7,OUTPUT);
  pinMode(motEsq15,OUTPUT);
  pinMode(motEsq10,OUTPUT);
}


void loop(){
  microSec = sensorUltrasonico.timing(); //recebendo o valor lido direto no sensor
  distancia = sensorUltrasonico.convert(microSec, Ultrasonic::CM); //converte o valor para centimetro, descartando os valores apos a virgula
  
  if(distancia >= 15){  //se distancia menor que 15 centimetros
    digitalWrite(2, HIGH);  //acende o teste para ver que o robo esta andando
    frente(); //executa a função frente que faz o carro andar para frente
    delay(100);  //o carro anda por 100 milessegundos
  }else{      
    digitalWrite(2, LOW); //apaga o teste para ver que o robo esta andando
    tras();
    delay(100);
    parado(); //executa a função parado que faz o carro parar
    delay(3000); // o carro fica parado por 3 segundos
  }  
  // mudaDirecao();
}

void frente(){ //observação os motores NÃO podem estar com os dois POLOS em HIGH
//sentido dos motores para andar para frente deve ser invertido
  digitalWrite(motDir2, HIGH);
  digitalWrite(motDir7, LOW);
    
  digitalWrite(motEsq10, LOW);
  digitalWrite(motEsq15, HIGH);
 //controle de velocida dos motores 
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

void mudaDirecao(){ //função para o robo girar
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
