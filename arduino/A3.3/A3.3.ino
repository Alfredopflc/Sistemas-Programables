//Pin de LEDS
const int LEDR = 17; 
const int LEDG = 18;
const int LEDB = 19;

//Canales de LEDS
const int Canal_R = 0;
const int Canal_G = 1;
const int Canal_B = 2;

const int frecuencia = 5000;

const int resolucion = 8; //8 bit

// Biblioteca Sensor de Temperatura
#include <Adafruit_Sensor.h>
#include "DHT.h"

//Pin del sensor DHT
const int DHTPIN = 16;                                
                                                                     
//Define el modelo del DHT
#define DHTTYPE DHT11    

//Variables para el DHT
DHT dht(DHTPIN, DHTTYPE);
float humedad;     
float humedad_actual;
float temperatura;  
float temperatura_actual;


void setup() {
  Serial.begin(115200);
  dht.begin(); //Metodo de libreria

  ////Se declaran los Pin para ser controlados
  ledcAttachPin(LEDR, Canal_R);
  ledcAttachPin(LEDG, Canal_G);
  ledcAttachPin(LEDB, Canal_B); 

  //Se configura el comportamiento de los LEDs a una frecuencia de 5000
  ledcSetup(Canal_R, frecuencia, resolucion);
  ledcSetup(Canal_G, frecuencia, resolucion);
  ledcSetup(Canal_B, frecuencia, resolucion);
}

void loop() {

  //Lectura del DHT
  humedad = dht.readHumidity();
  temperatura = dht.readTemperature();

  //Si no se detecta ningun valor, mandara mensaje
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("No se ha detectado DHT");
    delay(1000);
  }

  //Si existe un cambio de temperatura o humedad, imprimira los nuevos valores
  else if (humedad_actual != humedad || temperatura_actual != temperatura) {
      humedad_actual = humedad;  temperatura_actual = temperatura;

      //Imprime mensaje segun la temperatura
      if(temperatura >= 45){
        Serial.print("Temperatura alta: ");  
        Serial.print(temperatura);
        Serial.print("°");
        Serial.println("C");
      }

      if(temperatura <= 5){
        Serial.print("Temperatura baja: ");  
        Serial.print(temperatura);
        Serial.print("°");
        Serial.println("C");
      }

      if((temperatura > 5) && (temperatura < 45)) {     
        Serial.print("Temperatura ambiente: ");  
        Serial.print(temperatura);
        Serial.print("°");
        Serial.println("C");
      }

      Serial.print("Humedad:");
      Serial.print(humedad);
      Serial.println("%");
      Serial.println("====================");
    }

  //Si la temperatura supera los 45, el LED se prendera Rojo
  if(temperatura >= 45){
    RGB_Color(255,255,0); //Rojo (255,0,0)
  }

  //Si la temperatura es menor a 5, el LED se prendera Azul
  if(temperatura <= 5){
    RGB_Color(255,0,255); //Azul (0,0,255)
  }

  //Si la temperatura se mantiene entre 5 y 45, el LED se prendera Verde
  if((temperatura > 5) && (temperatura < 45)) {      
    RGB_Color(0,255,255); //Verde (0,255,0)
  }
    
}

//Metodo para cambiar el color del LED
void RGB_Color(int i, int j, int k)
{
  ledcWrite(Canal_R, i); 
  ledcWrite(Canal_G, j);
  ledcWrite(Canal_B, k); 
}
