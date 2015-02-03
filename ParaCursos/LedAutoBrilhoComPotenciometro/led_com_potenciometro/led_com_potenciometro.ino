/* by Samuel Moro Bergamo Cavalcante
   este código objetiva apresentar um led de auto brilho controlado
   via PWM, cujo varia com um potenciometro. 
   É um exercicio para praticar o entendimento do led RGB. 
   A ideia é apresentar também o uso de funções. 
*/
// ++ Variáveis do Programa ++
const int portaLedTeste = 5;
const int portaPotenciometroLedTeste = 0;
//const int portaPiezometro = 3; //teste pois leguei um Piezometro para 
const int temp0Sistema = 100;
int valorLidoSensorPotenciometroLedTeste = 0;
// -- Variáveis do Programa --

// ++ Declaração de Funções ++
int sensorPotenciometro();
void frequenciaLed(int frequencia);
// -- Fim Declaração de Funções --

// ++ código ++
void setup(){
  pinMode(portaLedTeste,OUTPUT);
}

void loop(){
  valorLidoSensorPotenciometroLedTeste = sensorPotenciometro();
  frequenciaLed(valorLidoSensorPotenciometroLedTeste);
}

int sensorPotenciometro(){
  return analogRead(portaPotenciometroLedTeste);
} 

void frequenciaLed(int frequencia){
  frequencia = map(frequencia, 0, 1023, 0, 255);
  analogWrite(portaLedTeste, frequencia);
//  analogWrite(portaPiezometro, frequencia);
}
