// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
#include <Ultrasonic.h>

#define TRIGGER 12
#define ECHO 11


Ultrasonic sensorUltrasonico (TRIGGER,ECHO);
int distancia; //Criada para receber o valor da distancia em cm
long microsec; //criada para auxiliar na equação do sensor de distancia 



Servo myservoDir;  // create servo object to control a servo 
Servo myservoEsq;  // create servo object to control a servo 

//FUNÇÕES DE parametros para fazer o rodar objeto
void parar();
void girarDir();
void girarEsq();
void andarReto();
void pararPorSensorLDR();
int lerDistancia();
 
int potpinDir = 1;  // analog pin used to connect the potentiometer
int potpinEsq = 2;  // analog pin used to connect the potentiometer
int potpinSensor = 5; //sensor LDR
int lineSensor = 5; //armazena a leitura do sensor
const int buttonPin = 7; //liga e deslica, será configurado com pull up interno.
const int segueLinha = 8; //liga o modulo seguidor de linha  com pull up interno.
int buttonState = HIGH; 
int distSensor = 4;
int sensorLumine = 0;
int velTurbo =10; //velocidade do metodo Turbo

int val;
int vel = 3;
int vel2 = 4;
int meio = 0;
int vmax = 0;
int vmin = 1024;
int meioDir = 0;    // variable to read the value from the analog pin 
int meioEsq = 0;    // variable to read the value from the analog pin 
int state = 0;
int counter = 0;
int diff = 0;
int objeto=0; //funciona como capitador de objeto
int soma = 8; 
int cond =0;

float p = 0.1;


 
void setup() 
{ 
  myservoDir.attach(5);  // Declara qual porta do Arduino o servo estará ligado
  myservoEsq.attach(6);  // 
  pinMode(buttonPin,INPUT); //pino 7 usado para estado de configuração
  digitalWrite(buttonPin,HIGH);//coloca o estado da porta como pull Up interno
  pinMode(segueLinha,INPUT);
  digitalWrite(buttonPin, HIGH); 
  pinMode(soma,INPUT);
  digitalWrite(soma,HIGH);
  pinMode(13,OUTPUT);
  pinMode(13,OUTPUT);
  state = 0;
  lerDistancia();
//  Serial.begin(9600);
} 
 
void loop(){ 
  //Define o estado inicial do sistema
  if (digitalRead(buttonPin)==LOW){
    state = 0;
  }else{
    if (state == 0)&&(digitalRead(buttonPin)==LOW){ 
      state = 3;
      counter = 0;
    }
  }
  //fim Define o estado inicial do sistema  
  //estado 0 é para regular os motores manualmente. 
  if (state == 0){
    val = analogRead(potpinDir);            // reads the value of the potentiometer (value between 0 and 1023) 
    meioDir = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    myservoDir.write(meioDir);                  // sets the servo position according to the scaled value 

    val = analogRead(potpinEsq);            // reads the value of the potentiometer (value between 0 and 1023) 
    meioEsq = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    myservoEsq.write(meioEsq);                  // sets the servo position according to the scaled value 
    delay(15);
    cond=0;
//fim estado 0, o código vai para o estado 1 dependendo da chave liga e desliga.
//Inicio estado 1 Regula o seguidor de linha
  }else if (state == 1){
    meio = analogRead(potpinSensor);
    if (meio > vmax) vmax = meio;
    if (meio < vmin) vmin = meio;
    if (counter < 50){
      myservoEsq.write(meioEsq+2);                  // sets the servo position according to the scaled value 
      myservoDir.write(meioDir+2);                  // sets the servo position according to the scaled value 
    }else if (counter < 100){
      myservoEsq.write(meioEsq-2);                  // sets the servo position according to the scaled value 
      myservoDir.write(meioDir-2);                  // sets the servo position according to the scaled value 
    }
    counter++;
    delay(20);
    if (counter > 100){
       meio = (vmax + vmin)/2;
       state = 2;
    }
//fim regula seguir linha
//Inicio Andar na linha
  }else if (state == 2){
    lineSensor = analogRead(potpinSensor);
    diff = (int)((float)(meio - lineSensor) * p);
    myservoEsq.write(meioEsq+vel+diff);
    myservoDir.write(meioDir-vel+diff);
    //modo turbo para subir a rampa.     
    if ((digitalRead(soma)==LOW)&&(cond==1)){
      vel = 5;
      digitalWrite(13,HIGH);
    }
    //Fim modo turbo para subir a rampa.     
    //--identifica objeto para desvio permite entrar no estado 3 
//    objeto = analogRead(distSensor);// lê o valor do sensor de distância 
//    if(objeto>600){ //distância maior que 600 entra no estado 3
//      digitalWrite(13,HIGH);
//      state = 3;
//    }
//fim andar na linha        

//Controle manual estado três
  }else if (state == 3){
    andarReto(vel2,100); //2500
    //-se grande incidencia de luz sobre o Robo ele irá parar até que essa incidencia diminua
    pararPorSensorLDR();
    turboSensor();
    if(lerDistancia() <= 15){
        parar(100); 
        girarDir(vel2,700); // de 450 para 430
        parar(100);
        while(lerDistancia() <=15){
          girarEsq((vel2),100); 
          //parar(100); 
        }
     }
     
     //CÓDIGO ANTIGO
     //  objeto = analogRead(distSensor);
     //  digitalWrite(13,LOW);
     //  state = 2;
     //  cond=1;    CÓDIGO ANTIGO FIM
  }
  //fim desvio objeto
} 

void turboSensor(){
  while(analogRead(sensorLumine) <250){
     andarReto(velTurbo,500);
     velTurbo ++;
  } 
}


void pararPorSensorLDR(){
  if(analogRead(sensorLumine) < 250){
    parar(1000);
  }  
}

int lerDistancia(){
  microsec= sensorUltrasonico.timing();
  distancia = sensorUltrasonico.convert(microsec,Ultrasonic::CM);
  return distancia;
}

void parar(int tempo){
    myservoEsq.write(meioEsq);
    myservoDir.write(meioDir);
    delay(tempo);
}
void girarDir(int veloc, int tempo){
    myservoEsq.write(meioEsq+veloc);
    myservoDir.write(meioDir+veloc);
    delay(tempo);
}
void girarEsq(int veloc, int tempo){
    myservoEsq.write(meioEsq-veloc);
    myservoDir.write(meioDir-veloc);
    delay(tempo);
}
void andarReto(int veloc, int tempo){
    myservoEsq.write(meioEsq+veloc);
    myservoDir.write(meioDir-veloc);
    delay(tempo);
}


