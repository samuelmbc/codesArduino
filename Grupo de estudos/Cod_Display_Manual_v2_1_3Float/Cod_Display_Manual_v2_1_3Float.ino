
const int vetorDisplay[] = {13,12,11,10};
const int D1 = 5;                        
const int D2 = 4;
const int D3 = 3;                
const int timeD = 5;                 
const int vezes = 10; 
float sensor;
/* O tempo de display acesso é 3*timeD*vezes
*/
                        // D,C,B,A
int matrizDados[10][4] = {{0,0,0,0}, //0
                          {0,0,0,1}, //1
                          {0,0,1,0}, //2
                          {0,0,1,1}, //3
                          {0,1,0,0}, //4
                          {0,1,0,1}, //5
                          {0,1,1,0}, //6
                          {0,1,1,1}, //7
                          {1,0,0,0}, //8
                          {1,0,0,1}}; //9
                       
int i,j,k,m,dado;
  
void setup() {                
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 //for(i=0;i<=110;i++){
   sensor=(analogRead(0)*500)/1023;
   imprime(sensor);   
// }
}

void imprime(float num){
   for(m=0;m<=vezes;m++){
      digitalWrite(D1,HIGH);   
      digitalWrite(D2,HIGH);
      digitalWrite(D3,LOW);
      j=num/100; //valor Centena    
      j=j%10;
      for(k=0;k<=3;k++){
        digitalWrite(vetorDisplay[k],matrizDados[j][k]);     
      }
      delay(timeD);
    
      digitalWrite(D1,HIGH);   
      digitalWrite(D2,LOW);
      digitalWrite(D3,HIGH);
      j=num/10; //valor Decimal    
      j=j%10;
      for(k=0;k<=3;k++){
        digitalWrite(vetorDisplay[k],matrizDados[j][k]);     
      }
      delay(timeD);
      
      digitalWrite(D1,LOW);   
      digitalWrite(D2,HIGH);
      digitalWrite(D3,HIGH);
      j=num%10; // valor unidade
      for(k=0;k<=3;k++){
         digitalWrite(vetorDisplay[k],matrizDados[j][k]);     
      }
      delay(timeD);
   }  
}

