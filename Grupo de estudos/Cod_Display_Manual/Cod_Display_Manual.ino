const int ledA = 13;
const int ledB = 12;
const int ledC = 11;
const int ledD = 10;
const int ledE = 9;
const int ledF = 8;
const int ledG = 7;
const int ledP = 6;

void APAGAR();
void UM();
void DOIS();
void TESTE();

void setup() {                
  pinMode(ledA, OUTPUT);    
  pinMode(ledB, OUTPUT);     
  pinMode(ledC, OUTPUT);      
  pinMode(ledD, OUTPUT);    
  pinMode(ledE, OUTPUT);     
  pinMode(ledF, OUTPUT);      
  pinMode(ledG, OUTPUT);      
  pinMode(ledP, OUTPUT);        
}


void loop() {
  TESTE();
  UM();
  delay(1000);
  APAGAR();
  delay(1000);
  DOIS();
  delay(1000);
  APAGAR();
  delay(1000);
}

void APAGAR(){
  digitalWrite(ledB, LOW);
  digitalWrite(ledC, LOW);
  digitalWrite(ledD, LOW);
  digitalWrite(ledE, LOW);
  digitalWrite(ledF, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledP, LOW);
  digitalWrite(ledA, LOW);
}

void UM(){
  digitalWrite(ledB, HIGH); 
  digitalWrite(ledC, HIGH);
}
 
void DOIS(){
  digitalWrite(ledA, HIGH); 
  digitalWrite(ledB, HIGH);
  digitalWrite(ledG, HIGH); 
  digitalWrite(ledE, HIGH);
  digitalWrite(ledD, HIGH); 
}  
void TESTE(){
  digitalWrite(ledA, HIGH);
  delay(500);
  digitalWrite(ledA, LOW);
  delay(20);
  digitalWrite(ledB, HIGH);
  delay(500);
  digitalWrite(ledB, LOW);
  delay(20);
  digitalWrite(ledC, HIGH);
  delay(500);
  digitalWrite(ledC, LOW);
  delay(20);
  digitalWrite(ledD, HIGH);
  delay(500);
  digitalWrite(ledD, LOW);
  delay(20);
  digitalWrite(ledE, HIGH);
  delay(500);
  digitalWrite(ledE, LOW);
  delay(20);
  digitalWrite(ledF, HIGH);
  delay(500);
  digitalWrite(ledF, LOW);
  delay(20);
  digitalWrite(ledG, HIGH);
  delay(500);
  digitalWrite(ledG, LOW);
  delay(20);
}

