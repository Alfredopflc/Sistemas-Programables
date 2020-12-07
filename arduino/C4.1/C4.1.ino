//Libreria para utilizar Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

//Constantes para declarar pin del LED
const int ledPin = 22;
String message = "";
char incomingChar;

void setup() {
  //LED como salida 
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  //Se asigna nombre para encontrar el ESP32 en Bluetooth
  SerialBT.begin("ESP32test"); //Bluetooth device name
  //Mensaje para indicar que se inicio la libreria Bluetooth
  Serial.println("The device started, now you can pair it with bluetooth!");
}
void loop() {
  //Si la libreria de Bluetooth esta activada va a leer el puerto serial
  if (SerialBT.available()){
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n'){
      message += String(incomingChar);
    }
    else{
      message = "";
    }
    Serial.write(incomingChar);  
  }
  // Si el mensaje es ON se prende el LED
  if (message =="ON"){
    digitalWrite(ledPin, HIGH);
  }

  //Si el mensaje es OFF se apaga el LED
  else if (message =="OFF"){
    digitalWrite(ledPin, LOW);
  }
  delay(20);
}
