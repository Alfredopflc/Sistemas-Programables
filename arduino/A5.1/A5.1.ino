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

Servo servo1;

#define S0 27
#define S1 26
#define S2 25
#define S3 33
#define sensorSalida 32
#define servoPin 13

int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;

void setup() {
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
                          // Configura el filtor ROJO para tomar lectura
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  delay(100);
  Rojo_Frec= pulseIn(sensorSalida, LOW);
  Serial.print(" R= "); Serial.print(Rojo_Frec);
  delay(100);
                            // Configura el filtor VERDE para tomar lectura
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  delay(100);
  Verde_Frec = pulseIn(sensorSalida, LOW);
  Serial.print(" V= "); Serial.print(Verde_Frec);
  delay(100);
                           // Configura el filtor AZUL para tomar lectura
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  delay(100);
  Azul_Frec = pulseIn(sensorSalida, LOW);
  Serial.print(" A= "); Serial.print(Azul_Frec);
  delay(100);

                  //Valores obtenidos en la calibracion del sensor, son propios de cada usuario 
 /*                 
 if (Rojo_Frec < 85 && Verde_Frec > 80 && Azul_Frec > 80)  Serial.print(" . *** ROJO **"); servo1.write(0);
 if (Rojo_Frec > 80 && Verde_Frec > 100 && Azul_Frec < 80)  Serial.print(" . *** AZUL **"); servo1.write(45);
 if (Rojo_Frec > 185 && Verde_Frec < 140 && Azul_Frec < 130)  Serial.print(" . *** VERDE **"); servo1.write(90);
 if (Rojo_Frec < 35 && Verde_Frec < 35 && Azul_Frec < 35)  Serial.print(" . *** BLANCO **"); servo1.write(135);
 if (Rojo_Frec > 130 && Verde_Frec > 200 && Azul_Frec >150)  Serial.print(" . *** NEGRO **"); servo1.write(180);
 */

if ( 460 > Rojo_Frec > 435 && 500 > Verde_Frec > 470 && 420 >Azul_Frec > 400)
{  
  Serial.println(" . *** NEGRO **");
  servo1.write(0); 
}

if (80 > Rojo_Frec > 70 && 280 > Verde_Frec > 265 && 220 > Azul_Frec > 200)
{
  Serial.println(" . *** ROJO **"); 
  servo1.write(45);  
}

if (280 > Rojo_Frec > 270 && 136 > Verde_Frec > 125 && 80 > Azul_Frec > 75)
{
  Serial.println(" . *** AZUL **"); 
  servo1.write(90);
}

if (50 > Rojo_Frec > 40 && 55 > Verde_Frec > 45 && 50 > Azul_Frec > 40)
{
  Serial.println(" . *** BLANCO **"); 
  servo1.write(135);  
}

if (295 > Rojo_Frec > 285 && 190 > Verde_Frec > 180 && 250 > Azul_Frec > 240)
{
  Serial.println(" . *** VERDE **"); 
  servo1.write(180);  
}

 Serial.println("*");
 delay(200);
}
