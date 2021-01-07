int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
 
// Propiedades PWM
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
 
void setup() {
  // Pines de salida
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // Configuracion LED PWM
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);
 
  Serial.begin(115200);
  Serial.print("Inicio de Motor");
}
 
void loop() {
  ledcWrite(pwmChannel, dutyCycle); 
  dutyCycle = 255;
  
  // Forward
  Serial.println("Motor en Movimiento");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(5000);
 
  // Se detiene el motor
  Serial.println("Motor Detenido");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);
 
  // Reversa
  Serial.println("Motor en Reversa");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(5000);
 
  // Se detiene el motor
  Serial.println("Motor Detenido");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);
  
}
