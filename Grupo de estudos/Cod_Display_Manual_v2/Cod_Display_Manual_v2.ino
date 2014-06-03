
const int vetorDisplay[] = {13,12,11,10};
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
                       
int i,j,k,dado;
  
void setup() {                
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  for(i=0;i<=9;i++){
    //j=defineNumero(i);
    for(k=0;k<=3;k++){
      digitalWrite(vetorDisplay[k],matrizDados[i][k]);     
      Serial.print(matrizDados[i][k]);
     }
     Serial.println(";");
     delay(500); 
    
  }
}

/*
int defineNumero(int num){
  switch (num) {
    case 0: dado=0;
      break;
    case 1: dado=1;
      break;
    case 2: dado=2;
      break;
    case 3: dado=3;
      break;
    case 4: dado=4;
      break;
    case 5: dado=5;
      break;
    case 6: dado=6;
      break;
    case 7: dado=7;
      break;
    case 8: dado=8;
      break;
    case 9: dado=9;
       break;
    }
    return dado;
}*/
