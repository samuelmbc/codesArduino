// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 

Servo myservoDir;  // create servo object to control a servo 
Servo myservoEsq;  // create servo object to control a servo 
 
int potpinDir = 1;  // analog pin used to connect the potentiometer
int potpinEsq = 2;  // analog pin used to connect the potentiometer
int potpinSensor = 5; //sensor LDR
int lineSensor = 5; //armazena a leitura do sensor
int buttonPin = 7; //liga e deslica, será configurado com pull up interno.
int buttonState = HIGH; 
int distSensor = 4;

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

//parametros para fazer o rodar objeto
void parar();
void girarDir();
void girarEsq();
void andarReto();
int soma = 8; 
int cond =0;

float p = 0.1;
 
void setup() 
{ 
  myservoDir.attach(5);  // Declara qual porta do Arduino o servo estará ligado
  myservoEsq.attach(6);  // 
  pinMode(buttonPin,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(buttonPin,HIGH);//coloca o estado da porta como pull Up interno
  pinMode(soma,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(soma,HIGH);
  state = 0;
} 
 
void loop() 
{ 
  //Define o estado inicial do sistema
  if (digitalRead(buttonPin)==LOW){
    state = 0;
  }else{
    if (state == 0){
      state = 1;
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
    objeto = analogRead(distSensor);// lê o valor do sensor de distância 
    if(objeto>600){ //distância maior que 600 entra no estado 3
      digitalWrite(13,HIGH);
      state = 3;
    }
//fim andar na linha        
//inicio estado 3 desvio do objeto
  }else if (state == 3){
    parar(100);
  //vira lado 1 e para
    girarDir(vel2,600); // de 450 para 430
    parar(100);
    
    andarReto(vel2,2300); //2500
    parar(100);

    girarEsq((vel2),800); 
    parar(100);

    andarReto(vel2,2400); //2700 para 2400
    parar(100);

    girarDir((vel2),300);
    parar(100);
    
    objeto = analogRead(distSensor);
    digitalWrite(13,LOW);
    state = 2;
    cond=1;    
  }
  //fim desvio objeto
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


