// Programa : Niveis de ruido com Sensor de Som  
// Autor : Arduino e Cia  

#define ledVermelho 10
#define ledAmarelo 9
#define ledVerde 8
   
const int num_leitura = 256; //Define o numero de medicoes  
int pinoSinalSensorSom = A0; //Pino ligado ao pino S do modulo sensor de som  
long sinalSensorSom;   //Armazena o valor lido do Sensor de Som  
long somaDeLeituras = 0; //Armazena o valor total das n medicoes  
long nivelSom =0; //Armazena o valor medio  
   
 
//Array para montar o simbolo grafico  
   
void setup()  
{   
  pinMode(pinoSinalSensorSom, INPUT); //Define o pino de sinal como Entrada  
  Serial.begin(9600);  
  pinMode(ledVermelho, OUTPUT);  
  pinMode(ledAmarelo, OUTPUT);  
  pinMode(ledVerde, OUTPUT);  
}  
   
void loop()  
{  
  //Efetua 128 leituras do sinal  
  for (int i=0; i<num_leitura ; i++)  
  { sinalSensorSom = analogRead(pinoSinalSensorSom);  
    somaDeLeituras = somaDeLeituras + sinalSensorSom;  
  }  
  nivelSom = somaDeLeituras/num_leitura; //Calcula o valor medio  
  digitalWrite(ledVermelho,LOW);    
  digitalWrite(ledAmarelo,LOW);    
  digitalWrite(ledVerde,LOW);      
  
  //Verifica o nivel de sinal e exibe na tela    
  if (nivelSom < 100)  
  {  
    Serial.print("Nivel Baixo");  
    Serial.print(" - Media : ");  
    Serial.println(nivelSom);  
    digitalWrite(ledVerde,HIGH);
  }  

  if (nivelSom >100 && nivelSom < 300 )  
  {  
    Serial.print("Nivel Medio");  
    Serial.print(" - Media : ");  
    Serial.println(nivelSom);  
    digitalWrite(ledAmarelo,HIGH);
  }  

  if (nivelSom > 300)  
  {  
    Serial.print("Nivel alto");  
    Serial.print(" - Media : ");  
    Serial.println(nivelSom);  
    digitalWrite(ledVermelho,HIGH);
  }  
  
  somaDeLeituras = 0; //Reinicia a soma dos valores das medicoes  
}  
