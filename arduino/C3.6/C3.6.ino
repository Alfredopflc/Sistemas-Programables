//Entrada GPI34 del NodeMCU
const int potPin = 34; 
//Variable para calcular el valor del potenciometro
int potValue = 0;

void setup() {
  //Se utilizara el monitor en serie
 Serial.begin(115200);
 //Delay de 1 segundo
 delay(1000);

}

void loop() {
  // Leer valor de potenciometro
  potValue = analogRead(potPin);
  //Imprime el valor del potenciometro
  Serial.println(potValue);
  //Delay de medio segundo
  delay(500);

}
