const int ledVermelho = 13;
const int botaoLedVermelho = 11;
const int ledAmarelo = 12;
const int botaoLedAmarelo = 10; 
int estado =0;
void setup(){
  pinMode(ledVermelho,OUTPUT);
  pinMode(botaoLedVermelho, INPUT);
  pinMode(ledAmarelo,OUTPUT);
  pinMode(botaoLedAmarelo, INPUT);
}

void loop(){
  //if(digitalRead(botaoLedVermelho)==1){
    digitalWrite(ledVermelho,HIGH);
    delay(50);
  //}else{
    digitalWrite(ledVermelho,LOW);
    delay(50);
  //}
  if(((digitalRead(botaoLedAmarelo)==1)&&(estado==0))){
    while(digitalRead(botaoLedAmarelo)==1){delay(50);}
    digitalWrite(ledAmarelo,HIGH);
    estado=1;
   }
   if(((digitalRead(botaoLedAmarelo)==1)&&(estado==1))){
    while(digitalRead(botaoLedAmarelo)==1){delay(50);}
    digitalWrite(ledAmarelo,LOW);
    estado=0;
   }
}

