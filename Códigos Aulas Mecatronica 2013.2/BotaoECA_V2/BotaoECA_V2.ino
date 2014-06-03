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
  if(digitalRead(botaoLedVermelho)==1){
    digitalWrite(ledVermelho,HIGH);
    delay(500);
  }else{
    digitalWrite(ledVermelho,LOW);
  }
  if(((digitalRead(botaoLedAmarelo)==1)&&(estado==0))){
    esperaSoltarBotao();
    digitalWrite(ledAmarelo,HIGH);
    estado=1;
   }
   if(((digitalRead(botaoLedAmarelo)==1)&&(estado==1))){
    esperaSoltarBotao();
    digitalWrite(ledAmarelo,LOW);
    estado=0;
   }
}


void esperaSoltarBotao(){
   while(digitalRead(botaoLedAmarelo)==1){delay(10);}
   while(digitalRead(botaoLedVermelho)==1){delay(10);}
}
