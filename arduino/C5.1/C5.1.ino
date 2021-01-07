int LDR = 34; 
int LDR_val = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  LDR_val = analogRead(LDR);
  Serial.println(LDR_val);
   
  delay(1000);
}
