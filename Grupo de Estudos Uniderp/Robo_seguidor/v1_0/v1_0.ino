// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo myservoDir;  // create servo object to control a servo 
Servo myservoEsq;  // create servo object to control a servo 
 
const int potpinDir = 1;  // analog pin used to connect the potentiometer
const int potpinEsq = 2;  // analog pin used to connect the potentiometer
const int potpinSensor = 5; // Sensor de Luminosidade ligado embaixo do Robo
int lineSensor = 0; //variavel para atuar em contas de posicionamento
const int buttonPin = 7;  //usado para ligar o Robo
//int buttonState = HIGH; 

int val;
int vel = 3;
int meio = 0;
int vmax = 0;
int vmin = 1024;
int meioDir = 0;    // variable to read the value from the analog pin 
int meioEsq = 0;    // variable to read the value from the analog pin 
int state = 0;
int counter = 0;
int diff = 0;

float p = 0.1;  // Variavel de compensação do PID

void setup(){ 
  myservoDir.attach(5);  // Declara qual porta do Arduino o servo estará ligado
  myservoEsq.attach(6);  // 
  pinMode(buttonPin,INPUT);
  digitalWrite(buttonPin,HIGH);//coloca o estado da porta como pull Up interno
  state = 0;
} 
 
void loop() 
{ 
  
  if (digitalRead(buttonPin)==LOW){
    state = 0;
  }else{
    if (state == 0){
      state = 1;
      counter = 0;
    }
  }
  
  if (state == 0){
    val = analogRead(potpinDir);            // reads the value of the potentiometer (value between 0 and 1023) 
    meioDir = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    myservoDir.write(meioDir);                  // sets the servo position according to the scaled value 

    val = analogRead(potpinEsq);            // reads the value of the potentiometer (value between 0 and 1023) 
    meioEsq = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
    myservoEsq.write(meioEsq);                  // sets the servo position according to the scaled value 
    delay(15);
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
  }else{
    lineSensor = analogRead(potpinSensor);
    diff = (int)((float)(meio - lineSensor) * p);
    myservoEsq.write(meioEsq+vel+diff);                  // sets the servo position according to the scaled value 
    myservoDir.write(meioDir-vel+diff);                  // sets the servo position according to the scaled value 
  } 
} 


