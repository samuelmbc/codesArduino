#include <EEPROM.h>

int endereco = 0;
float valor, sensor1, sensor2, sensor3, valorLido;
void setup()
{
  Serial.begin(9600);
  
}

void loop()
{ sensor1 = analogRead(0);
  sensor2 = analogRead(1);
  sensor3 = analogRead(2);  
  valor = (sensor1 + sensor2 + sensor3)/3;
  
  Serial.println(valor);
  setFloatEEPROM(0,valor);
  valorLido = getFloatEEPROM(0);
  Serial.println(valorLido);

  delay(5000);
}

//códgio de http://labdegaragem.com/forum/topics/ajuda-para-gravar-numero-de-tel-na-eeprom?commentId=6223006%3AComment%3A288922
void setFloatEEPROM(int posicao, float valor){ //grava na eeprom, chame o metodos e passe a posição e o valor
  float num = valor;
  float *P_num = &num;
  byte *P_num2 = (byte*)P_num;
  byte a = *P_num2;
  byte b = *(P_num2 + 1);
  byte c = *(P_num2 + 2);
  byte d = *(P_num2 + 3);
  EEPROM.write(posicao, a);
  EEPROM.write(posicao+1, b);
  EEPROM.write(posicao+2, c);
  EEPROM.write(posicao+3, d);
}
float getFloatEEPROM(int posicao){//faz a leitura do valor e retorna em float
  byte a = EEPROM.read(posicao);
  byte b = EEPROM.read(posicao+1);
  byte c = EEPROM.read(posicao+2);
  byte d = EEPROM.read(posicao+3); 
  float result = 0;
  float *P_num = &result;
  byte *P_num2 = (byte*)P_num;
  *P_num2 = (byte) a;
  *P_num2++;
  *P_num2 = (byte) b;
  *P_num2++;
  *P_num2 = (byte) c;
  *P_num2++;
  *P_num2 = (byte) d;
  return (float)result;
}
