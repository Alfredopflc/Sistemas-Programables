//Se declaran los pines GPIO16 para el LED u GPIO4 para el touch
const int touchPin = 4;
const int ledPin = 16;

//Cambiar con el valor umbral
const int threshold = 20;
//Variable para almacenar el valor del pin touch
int touchValue;

void setup() {
  //Iniciar comunicacion con el monitor en serie
  Serial.begin(115200);
  delay(1000);
  //Asignamos el LED como salida
  pinMode(ledPin,OUTPUT);

}

void loop() {
  //Lee el estado del pin touch
  touchValue = touchRead(touchPin);
  //Se imprime el valor obtenido del pin touch
  Serial.print(touchValue);

  //Si el valor del pin touch es menor al umbral, se prende el led e imprime "LED encendido"
  if(touchValue < threshold){
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }

  //Si no, entonces el LED se apaga e imrpime "LED apagado"
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("- LED off");
  }
