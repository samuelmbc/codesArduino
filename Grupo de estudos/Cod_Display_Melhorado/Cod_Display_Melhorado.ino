const int time = 5;
int milhar_v[] = {0,0,0,0}; //declaração vetor milhar
int centena_v[] = {0,0,0,0}; //declaração vetor centena
int dezena_v[] = {0,0,0,0}; //declaração vetor dezena
int unidade_v[] = {0,0,0,0}; //declaração vetor unidade
int numero, unidade, dezena, centena, milhar; // Variaveis globais de apoio a definição do valor
int k, porta, time2; // variaveis globais de apoio na contagem de tempo
int cond=0; 
     
void setup(){
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(11, OUTPUT); 
  pinMode(10, OUTPUT);

  pinMode(8, INPUT);  //botão
  
  pinMode(5, OUTPUT); //Controle Milhar
  pinMode(4, OUTPUT); //Controle Centena
  pinMode(3, OUTPUT); //Controle Dezena
  pinMode(2, OUTPUT); //Controle Unidade
  Serial.begin(9600);
}

void loop(){
  
//  cond = digitalRead(8);
  
  if(cond == 1){ 
    sensor();
    cond = digitalRead(8);
    
  }else{
    numero=0;
    while((numero<=9999)&&(cond==0)){ //entra no laço de repetição contando até 9999
//    for(numero=0;numero<=9999;numero++)
      numero++; //incrementa o número a ser contado
      unidade = numero%10; //coloca na unidade o resto do número
      decimal_binario(unidade,unidade_v); // Chama a função de conversão decimal Binário - Carrega o vetor Unidade
  
      dezena = numero/10; //divide por 10, para gerar a unidade.
      dezena = dezena%10; //coloca na unidade o resto do número
      decimal_binario(dezena,dezena_v);// Chama a função de conversão decimal Binário - Carrega o vetor Unidade
       
      centena = numero/100;
      centena = centena%10;
      decimal_binario(centena,centena_v);// Carrega o vetor Centena
       
      milhar = numero/1000; //transforma o milhar em decimal
      milhar = milhar%10; //pega o resto do decimal
      decimal_binario(milhar,milhar_v); // Carrega o vetor milhar
      
      time2 = 5; // determina quantas vezes será executada a impressão, isso percurte no tempo de amostra
      imprime_numero(); // Função para imprimir o número 
      
      cond = digitalRead(8);
      if(numero%300==0)
        sensor();
      if(cond==1)
        numero=9999;
    }
  }
}

void decimal_binario(int num,int bits[]){
  bits[0]=0; bits[1]=0; bits[2]=0; bits[3]=0;
  switch (num) {
    case 0: 
      break;
    case 1: bits[3]=1; //0001
      break;
    case 2: bits[2]=1; //0010
      break;
    case 3: bits[2]=1; bits[3]=1;
      break;
    case 4: bits[1]=1;
      break;
    case 5: bits[1]=1; bits[3]=1;
      break;
    case 6: bits[1]=1; bits[2]=1;
      break;
    case 7: bits[1]=1; bits[2]=1; bits[3]=1;
      break;
    case 8: bits[0]=1;
      break;
    case 9: bits[0]=1; bits[3]=1;
      break;
  }
  //Observação: nesse codigo colocamos o vetor em 0 e depois 
  //            passamoa acionar cada bit especifico, conforme a numeração.
}

void imprime_numero(){
//Apagando a unidade Dezena e Centena
  digitalWrite(2, HIGH);  
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
// - Executa o código de impressão varias vezes dando a impressão de alta luminosidade.
  for(int x=0;x<=time2;x++){
//Digito Das Milhar (DCBA)
    digitalWrite(2, HIGH);
    digitalWrite(5, LOW);
    porta = 10;
    for(k=0;k<4;k++){
      digitalWrite(porta,milhar_v[k]);
      porta++;
    }
    delay(time);
//Digito Das Centena (DCBA)
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    porta = 10;
    for(k=0;k<4;k++){
      digitalWrite(porta,centena_v[k]);
      porta++;
    }
    delay(time);
//Digito Das Dezenas (DCBA)
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    porta = 10;
    for(k=0;k<4;k++){
      digitalWrite(porta,dezena_v[k]);
      porta++;
    }
    delay(time);
//Digito Das Unidades (DCBA)
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);         
    porta = 10;
    for(k=0;k<4;k++){
      digitalWrite(porta,unidade_v[k]);
      porta++;
    }
    delay(time);
  }
}
void sensor(){
    numero = analogRead(4);
    numero = (5*numero*100)/1024; //não sei por que o valor esta saindo negativo.
    Serial.println(numero);   
    unidade = numero%10;
    decimal_binario(unidade,unidade_v); // Carrega o vetor Unidade

    dezena = numero/10;
    dezena = dezena%10; 
    decimal_binario(dezena,dezena_v);// Carrega o vetor Dezena

    decimal_binario(0,centena_v);// Carrega 0 no vetor Centena
    decimal_binario(0,milhar_v); // Carrega 0 no vetor milhar
    time2 = 500; // determina quantas vezes será executada a impressão, isso percurte no tempo de amostra
    imprime_numero(); // Função para imprimir o número 
}
