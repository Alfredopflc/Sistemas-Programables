//Seleccionamos que el GPIO16 sera la que usaremos
const int ledPin = 17;

//Propiedades de PWM
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  //Se configura el comportamiento del LED a una frecuencia de 5000
  ledcSetup(ledChannel, freq, resolution);
  //Aqui se declara el ledPin para ser controlado
  ledcAttachPin(ledPin, ledChannel);

}

void loop() {
  //Incrementa el brillo del LED cuando el valor de dutyCycle es igual o menor a 255
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
    //se cambia el brillo del LED segun el valor de dutyCycle
    ledcWrite(ledChannel, dutyCycle);
    delay(25);
  }

  delay(1000);
  
  //Disminuye el brillo del LED cuando el valor de dutyCycle es 255
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    //se cambia el brillo del LED segun el valor de dutyCycle
    ledcWrite(ledChannel, dutyCycle);
    delay(25);
  }

  delay(1000);
}
