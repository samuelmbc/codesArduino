
const int vetorDisplay[] = {0,12,11,10,9,8,7,6,13};
//int vB_2[8] = {1,1,1,1,1,1,1,1};
int vB1[] = {1,1,1,1,1,1,1,1,1};
int i,j,k;

  
void setup() {                
  for(i=0;i<=9;i++)
    pinMode(vetorDisplay[i], OUTPUT);     
}

void APAGAR();
void CARREGA();
void carregaNumero();


void loop() {
  for(i=0;i<=9;i++){
    APAGAR();
    CARREGA();
    carregaNumero(i,vB1);
    CARREGA();
    delay(200);
    APAGAR();
    delay(200);
    CARREGA();
    delay(200);
  }
}

void CARREGA(){
  for(j=0;j<=9;j++)
      digitalWrite(vetorDisplay[j], vB1[j]);
}

void APAGAR(){
  for(k=0;k<=9;k++)
    vB1[k]=0;
}

//vB[0]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;vB[6]=1;vB[7]=1;
void carregaNumero(int num, int vB[]){
//  APAGAR();
  switch (num) {
    case 0: vB[8]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;
      break;
    case 1: vB[1]=1; vB[2]=1;
      break;
    case 2: vB[8]=1;vB[1]=1;vB[3]=1;vB[4]=1;vB[6]=1;
      break;
    case 3: vB[8]=1;vB[1]=1; vB[2]=1;vB[3]=1;vB[6]=1;//vB[7]=1;
      break;
    case 4: vB[1]=1; vB[2]=1;vB[5]=1;vB[6]=1;//vB[7]=1;
      break;
    case 5: vB[8]=1;vB[2]=1;vB[3]=1;vB[5]=1;vB[6]=1;//vB[7]=1;
      break;
    case 6: vB[8]=1;vB[2]=1;vB[3]=1;vB[4]=1;vB[5]=1;vB[6]=1;//vB[7]=1;
      break;
    case 7: vB[8]=1;vB[1]=1;vB[2]=1;
      break;
    case 8: 
      for(k=1;k<=9;k++)
              vB[k]=1;
      vB[7]=0;
      break;
    case 9: vB[8]=1;vB[1]=1;vB[2]=1;vB[3]=1;vB[5]=1;vB[6]=1;
      break;
    }
}
