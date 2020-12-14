int LDR = 34; 
int LDR_val = 0;
int relay = 16; 

void setup() {
  Serial.begin(9600);
  pinMode(relay,OUTPUT);
}

void loop() {
  LDR_val = analogRead(LDR);
  Serial.println(LDR_val);

  if(LDR_val >= 500){
    digitalWrite(relay,LOW);
  }

   else{
    digitalWrite(relay,HIGH);
  }
  
  delay(1000);
}
