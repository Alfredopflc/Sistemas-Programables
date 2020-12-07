//Libreria para utilizar Bluetooth
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;

// Variables del mensaje
String message = "";
char incomingChar;
bool valor = true;

// Pin del motor
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
 
void setup() {
  // Salidas del motor
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
   
  Serial.begin(115200);

  //Se asigna nombre para encontrar el ESP32 en Bluetooth
  SerialBT.begin("ESP32test"); //Bluetooth device name
  
  //Mensaje para indicar que se inicio la libreria Bluetooth y motor
  Serial.println("Iniciando conexion con el Bluetooth");
  Serial.print("Iniciando motor");  
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

  // Si el mensaje es 1 inicia el ciclo 
  if (message == "1"){
    while(valor == true){
      // Forward
      Serial.println("");
      Serial.println("Motor en movimiento");
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor1Pin1, HIGH);
      for(int i = 0; i <= 50; i++)
      {
          delay(100); 
          Leer();    
          if (message == "0")
          {
            goto detener;
          }
      }
     
      // Se detiene el motor
      Serial.println("Motor detenido");
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor1Pin1, LOW);
      for(int i = 0; i <= 10; i++)
      {
        delay(100);
        Leer(); 
        if (message == "0")
        {
          goto detener;
        }
    }
 
      // Reversa
      Serial.println("Motor en reversa");
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor1Pin1, LOW); 
      for(int i = 0; i <= 50; i++)
      {
        delay(100);
        Leer(); 
        if (message == "0")
        {
          goto detener;
        }
      }
 
      // Se detiene el motor
      Serial.println("Motor detenido");
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor1Pin1, LOW);
      for(int i = 0; i <= 10; i++)
      {
        delay(100);
        Leer(); 
        if (message == "0")
        {
          goto detener;
        }
      }
    }
  }
    //Si el mensaje es STOP se apaga el motor
    if (message == "0"){ 
      detener:  
      //valor = false;
      Serial.println("");
      Serial.println("Motor detenido");
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor1Pin1, LOW);
      delay(1000);
    }
    delay(20); 
}

void Leer()
{
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
}
