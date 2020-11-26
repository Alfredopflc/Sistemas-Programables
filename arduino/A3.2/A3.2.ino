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
int valor = 0;
bool estado = false;

void setup() {
  //Iniciar comunicacion con el monitor en serie
  Serial.begin(115200);
  delay(1000);
 
  ledcSetup(ledChannel, freq, resolution);
  //Aqui se declara el ledPin para ser controlado
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  //Lee el estado del pin touch
  touchValue = 21;
  touchValue = touchRead(touchPin);
  //Se imprime el valor obtenido del pin touch
  Serial.println(touchValue);

  //Si esta apagado, se prende el LED poco a poco
    if((touchValue < threshold) && (estado == false)){  
      for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){
      ledcWrite(ledChannel, dutyCycle);
      delay(25);
      }   
            
    Serial.println(" - LED on");
    estado = true;
    touchValue = 21;
    delay(1000);
    }

  //Si esta prendido, el led apagara, prendera y apagara    
  if((touchValue < 20) && (estado == true)){
    ledcWrite(ledChannel, 0);
    delay(1000);
    ledcWrite(ledChannel, 255);
    delay(1000);
    ledcWrite(ledChannel, 0);
    delay(1000);
    
    Serial.println(" - LED off");
    estado = false;
    touchValue = 21;
    delay(1000);
  } 

 delay(500);
}
