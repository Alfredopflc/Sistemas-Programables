
//Variable para calcular el valor del potenciometro
int potValue = 0;

void setup() {
 pinMode(A0, INPUT);
 Serial.begin(9600);

}

void loop() {
  // Leer valor de potenciometro
  potValue = analogRead(A0);
  Serial.println(potValue);
  delay(1000);

}
