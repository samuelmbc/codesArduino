
const int vetorDisplay[8] = {13,12,11,10,9,8,7,6};
//int vB_2[8] = {1,1,1,1,1,1,1,1};
int vB[8] = {1,1,1,1,1,1,1,1};
int i,j,k;

  
void setup() {                
  for(i=0;i<=8;i++)
    pinMode(vetorDisplay[i], OUTPUT);     
}

void APAGAR();
void CARREGA();
void carregaNumero(int num);


void loop() {
  
  for(i=0;i<=9;i++){
    APAGAR();
    CARREGA();
    carregaNumero(i);
    CARREGA();
    delay(500);
  }
}

void CARREGA(){
  for(j=0;j<=8;j++)
      digitalWrite(vetorDisplay[j], vB[j]);
}

void APAGAR(){
  for(k=0;k<=8;k++)
    vB[k]=0;
}

//vB[0]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;vB[6]=1;vB[7]=1;
void carregaNumero(int num){
//  APAGAR();
  switch (num) {
    case 0: vB[0]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;
      break;
    case 1: vB[1]=1; vB[2]=1;
      break;
    case 2: vB[0]=1;vB[1]=1;vB[3]=1;vB[4]=1;vB[6]=1;
      break;
    case 3: vB[0]=1;vB[1]=1; vB[2]=1;vB[3]=1;vB[6]=1;vB[7]=1;
      break;
    case 4: vB[1]=1; vB[2]=1;vB[5]=1;vB[6]=1;vB[7]=1;
      break;
    case 5: vB[0]=1;vB[2]=1;vB[3]=1;vB[5]=1;vB[6]=1;vB[7]=1;
      break;
    case 6: vB[0]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;vB[6]=1;vB[7]=1;
      break;
    case 7: vB[0]=1;vB[4]=1;vB[5]=1;
      break;
    case 8: vB[0]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;vB[6]=1;vB[7]=1;
      break;
    case 9: vB[0]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[5]=1;vB[6]=1;vB[7]=1;
      break;
    }
}
