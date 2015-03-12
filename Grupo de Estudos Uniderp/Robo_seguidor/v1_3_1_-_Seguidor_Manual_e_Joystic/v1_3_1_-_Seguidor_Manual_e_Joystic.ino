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
void andarTras();
void desvioSensorDistancia();
void andarJoyStick();
 
int potpinDir = 1;  // analog pin used to connect the potentiometer
int potpinEsq = 2;  // analog pin used to connect the potentiometer
int potpinSensor = 5; //sensor LDR
int lineSensor = 5; //armazena a leitura do sensor
const int buttonLigaRobo = 7; //liga e deslica, será configurado com pull up interno.
const int segueLinha = 8; //liga o modulo seguidor de linha  com pull up interno.
const int buttonJoyStick = 9; //liga e deslica, será configurado com pull up interno.
int buttonState = HIGH; 
int distSensor = 4;
int sensorLumine = 0;
int velTurbo =10; //velocidade do metodo Turbo

int JoyStick_X = A3; //x
int JoyStick_Y = A4; //y
int JoyStick_Z = 3; //key digital


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
  pinMode(buttonLigaRobo,INPUT); //pino 7 usado para estado de configuração
  digitalWrite(buttonLigaRobo,HIGH);//coloca o estado da porta como pull Up interno
  pinMode(segueLinha,INPUT); //pino 8 usado para estado de configuração
  digitalWrite(buttonLigaRobo, HIGH); 
  pinMode(buttonJoyStick,INPUT); //pino 8 usado para estado de configuração
  digitalWrite(buttonJoyStick, HIGH); 
  pinMode(soma,INPUT);
  digitalWrite(soma,HIGH);
  pinMode(13,OUTPUT);
  state = 0;
  lerDistancia();
  pinMode(JoyStick_Z, INPUT); 
  Serial.begin(9600);
} 
 
void loop(){ 
  //Define o estado inicial do sistema
  if (digitalRead(buttonLigaRobo)==LOW){ //Pino 7 ligado no GND
    state = 0;
    Serial.println("status 0 ");
  }else{
    if ((state == 0)&&(digitalRead(segueLinha)==HIGH)){ //pino8 desligado com PullUp interno
      state = 1; //Regula Seguidor de linha
      counter = 0;
      Serial.println("Segue linha");
    }else if ((state == 0)&&(digitalRead(buttonJoyStick)==LOW)){ //pino8 em e 9 no gnd
        state = 3; //Controle Manual
        counter = 0;      
        Serial.println("Controle Manual");
     }else if((state == 0)&&(digitalRead(buttonJoyStick)==HIGH)){  //pino 9 no VCC
       state = 4; //Controle JoyStick
       counter = 0;
       Serial.println("JoyStick");      
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
       state = 2; //andar na linha
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
//fim andar na linha        

//Controle manual estado três
  }else if (state == 3){
    andarReto(vel2,1000); //2500
    //-se grande incidencia de luz sobre o Robo ele irá parar até que essa incidencia diminua
    pararPorSensorLDR();
    turboSensor();
    desvioSensorDistancia();
  }else if (state == 4){
    while(digitalRead(JoyStick_Z)==LOW){
      andarJoyStick();
      pararPorSensorLDR();
    }
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
void andarTras(int veloc,int tempo){
    myservoEsq.write(meioEsq-veloc);
    myservoDir.write(meioDir+veloc);
    delay(tempo);
}
void  desvioSensorDistancia(){
  if(lerDistancia() <= 15){
    parar(100); 
    girarDir(vel2,700); // de 450 para 430
    parar(100);
    while(lerDistancia() <=15){
      girarEsq((vel2),100); 
    }
   }
}


void andarJoyStick(){
    while(analogRead(JoyStick_Y)>700){ //frente Y acima de 700 
      andarReto(vel2+10,100);
      desvioSensorDistancia();
      Serial.println("Frente");     
    }
    while(analogRead(JoyStick_Y)<300){ //Trás y abaixo de 300 
      andarTras(vel2,100);
      desvioSensorDistancia();
      Serial.println("Trás");     
    }
    while(analogRead(JoyStick_X)>700){ //Esquerda x acima de 700
      girarEsq((vel2),100);
      desvioSensorDistancia();
      Serial.println("Esquerda");     
    }
    while(analogRead(JoyStick_X)<300){ //Direita x abaixo de 300
        girarDir((vel2),100);
        desvioSensorDistancia();
        Serial.println("Direita");     
    }
    parar(100);
}
