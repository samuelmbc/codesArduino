const int D = 13;
const int C = 12;
const int B = 11;
const int A = 10;
const int centena = 3; //LOW - Ativa e HIGH - desativa a Centena
const int dezena = 4; //LOW - Ativa e HIGH - desativa a Dezena
const int unidade = 5;

void TESTE();
void ZERO();
void UM();
void DOIS();
void TRES();
void APAGAR();


void setup() {                
  pinMode(D, OUTPUT);    
  pinMode(C, OUTPUT);     
  pinMode(B, OUTPUT);      
  pinMode(A, OUTPUT);    
  pinMode(5, OUTPUT); //Display unidade     
  pinMode(4, OUTPUT); //Display Dezena      
  pinMode(3, OUTPUT); //Display Centena
}


void loop() {
  digitalWrite(unidade, HIGH);
  digitalWrite(dezena, HIGH);
  digitalWrite(centena, HIGH);
  
  digitalWrite(centena, LOW);
  ZERO();
    APAGAR();
  digitalWrite(dezena, LOW);
  UM();
    APAGAR();
  digitalWrite(unidade, LOW);
  DOIS();
    APAGAR();

  digitalWrite(unidade, LOW);
  digitalWrite(dezena, LOW);
  digitalWrite(centena, LOW);
  TRES();
    APAGAR();

}


void APAGAR(){
  delay(900);
  digitalWrite(unidade, HIGH);
  digitalWrite(dezena, HIGH);
  digitalWrite(centena, HIGH);
  delay(100);
/*  digitalWrite(unidade, LOW);
  digitalWrite(dezena, LOW);
  digitalWrite(centena, LOW);
  */
}

void ZERO(){
  digitalWrite(D, LOW); 
  digitalWrite(C, LOW); 
  digitalWrite(B, LOW); 
  digitalWrite(A, LOW); 
}

void UM(){
  digitalWrite(D, LOW); 
  digitalWrite(C, LOW); 
  digitalWrite(B, LOW); 
  digitalWrite(A, HIGH); 
  

}
 
void DOIS(){
  digitalWrite(D, LOW); 
  digitalWrite(C, LOW); 
  digitalWrite(B, HIGH); 
  digitalWrite(A, LOW); 

}

void TRES(){
  digitalWrite(D, LOW); 
  digitalWrite(C, LOW); 
  digitalWrite(B, HIGH); 
  digitalWrite(A, HIGH); 

}


