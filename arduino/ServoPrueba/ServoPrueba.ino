#include <ESP32Servo.h>

Servo servo1;
#define servoPin 13

void setup() {
  servo1.attach(servoPin);
  
  Serial.begin(9600);
}

void loop() {
  servo1.write(0);
  delay(1000);
  servo1.write(45);
  delay(1000);
  servo1.write(90);
  delay(1000);
  servo1.write(135);
  delay(1000);
  servo1.write(180);
  delay(1000);

}
