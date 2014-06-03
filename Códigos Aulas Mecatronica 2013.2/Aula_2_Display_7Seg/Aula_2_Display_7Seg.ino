const int D = 13;
const int C = 12;
const int B = 11;
const int A = 10;

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
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  
  ZERO();
    APAGAR();
  UM();
    APAGAR();
  DOIS();
    APAGAR();
  TRES();
    APAGAR();   

}


void APAGAR(){
  delay(500);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(3, HIGH);

  delay(500);
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
  digitalWrite(3, LOW);
  
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


