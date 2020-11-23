//Se declaran los pines GPIO16 para el LED u GPIO4 para el touch
const int touchPin = 4;
const int ledPin = 17;

//Cambiar con el valor umbral
const int threshold = 20;
//Variable para almacenar el valor del pin touch
int touchValue;

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  //Iniciar comunicacion con el monitor en serie
  Serial.begin(115200);
  delay(1000);
  //Asignamos el LED como salida
 

  ledcSetup(ledChannel, freq, resolution);
  //Aqui se declara el ledPin para ser controlado
  ledcAttachPin(ledPin, ledChannel);

}

void loop() {
  //Lee el estado del pin touch
  touchValue = touchRead(touchPin);
  //Se imprime el valor obtenido del pin touch
  Serial.print(touchValue);

  //Si el valor del pin touch es menor al umbral, se prende el led e imprime "LED encendido"
  if(touchValue < threshold){
      for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    //se cambia el brillo del LED segun el valor de dutyCycle
    ledcWrite(ledChannel, dutyCycle);
    delay(20);
      }
      
    ledcWrite(ledChannel, 0);
    delay(1000);
    ledcWrite(ledChannel, 255);
    delay(1000);
    ledcWrite(ledChannel, 0);
    delay(1000);
   
    Serial.println(" - LED on");
  }

  //Si no, entonces el LED se apaga e imrpime "LED apagado"
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("- LED off");
  }

 delay(500);
}
