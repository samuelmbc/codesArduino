const int ledVermelho = 13;
const int botaoLedVermelho = 11;
const int ledAmarelo = 12;
const int botaoLedAmarelo = 10; 
int estado =3;
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
  if(((digitalRead(botaoLedAmarelo)==1)&&(estado==1))){
    estado=0;
  }
  while(((digitalRead(botaoLedAmarelo)==1)||(estado==0))){
    digitalWrite(ledAmarelo,HIGH);
    delay(500);
    digitalWrite(ledAmarelo,LOW);
    delay(500);
    estado = 0;
    while(digitalRead(botaoLedAmarelo)==1){delay(50);}
    if(((digitalRead(botaoLedVermelho)==1)&&(estado==0)))
        estado=1;
   }


}

