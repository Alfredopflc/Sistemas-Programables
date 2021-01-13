#include <ESP32Servo.h>

// Sensor de Color
//
//    Arduino   TCS230 SENSOR COLOR
//      32         OUT
//      33         S3
//      25         S2
//      26         S1
//      27         S0
//      5V        VCC
//      GND       GND

//Objeto servo
Servo servo1;

//Declarar salidas
#define S0 27
#define S1 26
#define S2 25
#define S3 33
#define sensorSalida 32
#define servoPin 13

//Variables RGB
int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;

void setup() {
  //Pines RGB
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorSalida, INPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  servo1.attach(servoPin);
  
  Serial.begin(9600);
}
void loop() {
// Configura el filtro ROJO para tomar lectura
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  delay(100);
  Rojo_Frec= pulseIn(sensorSalida, LOW);
//  Serial.print(" R= "); Serial.print(Rojo_Frec);
  delay(100);
  
// Configura el filtro VERDE para tomar lectura
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  delay(100);
  Verde_Frec = pulseIn(sensorSalida, LOW);
 // Serial.print(" V= "); Serial.print(Verde_Frec);
  delay(100);
  
// Configura el filtro AZUL para tomar lectura
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  delay(100);
  Azul_Frec = pulseIn(sensorSalida, LOW);
 // Serial.print(" A= "); Serial.print(Azul_Frec);
  delay(100);

//Rango de colores
if (Rojo_Frec < 100 && Verde_Frec > 250 && Azul_Frec > 200) //Rojo
{
  Serial.println(2); 
  servo1.write(0);  
}

else if (Rojo_Frec > 270 && Verde_Frec < 200 && Azul_Frec < 100) //Azul
{
  Serial.println(1); 
  servo1.write(90);
}

else if (Rojo_Frec > 280 && Verde_Frec < 250 && Azul_Frec < 300) //Verde
{
  Serial.println(0); 
  servo1.write(180);  
}

 delay(200);
}
