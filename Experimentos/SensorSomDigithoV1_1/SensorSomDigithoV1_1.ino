// Programa : Niveis de ruido com Sensor de Som  
// Autor : Arduino e Cia  
#include <Servo.h> 
Servo servoSino; 
   
const int num_leitura = 256; //Define o numero de medicoes  
int pinoSinalSensorSom = A0; //Pino ligado ao pino S do modulo sensor de som  
long sinalSensorSom;   //Armazena o valor lido do Sensor de Som  
long somaDeLeituras = 0; //Armazena o valor total das n medicoes  
long nivelSom =0; //Armazena o valor medio  
int direitoDeTossir=0; //criada para funcinar como um contador para casos de saude tosse e espiro. 

const int vetorPinos[] = {8,7,6,5,4,3,2};
int matrizEstado[8][7] = {{0,0,0,0,0,0,0}, //0
                         {0,0,0,0,0,0,1}, //1
                         {0,0,0,0,0,1,1}, //2
                         {0,0,0,0,1,1,1}, //3
                         {0,0,0,1,1,1,1}, //4
                         {0,0,1,1,1,1,1}, //5
                         {0,1,1,1,1,1,1}, //6
                         {1,1,1,1,1,1,1}}; //7

 
 
//Array para montar o simbolo grafico  
   
void setup()  
{   
  pinMode(pinoSinalSensorSom, INPUT); //Define o pino de sinal como Entrada  
  Serial.begin(9600);  
  pinMode(2, OUTPUT);  
  pinMode(3, OUTPUT);  
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT);  
  pinMode(7, OUTPUT);  
  pinMode(8, OUTPUT); 
  servoSino.attach(9);  //define a porta de ligação do Servo Motor

}  
   
void loop()  
{  
  //Efetua 128 leituras do sinal  
  for (int i=0; i<num_leitura ; i++)  
  { sinalSensorSom = analogRead(pinoSinalSensorSom);  
    somaDeLeituras = somaDeLeituras + sinalSensorSom;  
  }  
  nivelSom = somaDeLeituras/num_leitura; //Calcula o valor medio  

  //Verifica o nivel de sinal e exibe na tela    
  if (nivelSom < 100)  
  {  
    Serial.print("Nivel Baixo");  
    Serial.println(nivelSom);
    estadoNivel(0);     
    if (nivelSom > 20)  
      estadoNivel(1);    
    if (nivelSom > 50)  
      estadoNivel(2);
    if (nivelSom > 80)  
      estadoNivel(3);
  }  
 
  if (nivelSom >100 && nivelSom < 300 )  
  {  
    Serial.print("Nivel Medio");  
    Serial.println(nivelSom);  
    estadoNivel(3);     
    if (nivelSom > 150)  
      estadoNivel(4);    
    if (nivelSom > 200)  
      estadoNivel(5);
    if (nivelSom > 250)  
      estadoNivel(6);
  }  

  if (nivelSom > 280)  
  {  
    Serial.print("Nivel alto");  
    Serial.println(nivelSom);  
    estadoNivel(7);
    direitoDeTossir++; //contador para casos de saúde
    if(direitoDeTossir>2){
      bateNoSino();
      bateNoSino();
    }
  }  
  
  somaDeLeituras = 0; //Reinicia a soma dos valores das medicoes  
  
}  

void estadoNivel(int estadoSom){
  for(int k=0;k<=7;k++){
    digitalWrite(vetorPinos[k],matrizEstado[estadoSom][k]);    
 }
}

void bateNoSino(){
  servoSino.write(180);                
  delay(250);  
  servoSino.write(90); 
  delay(250);  
  direitoDeTossir=0;
}

