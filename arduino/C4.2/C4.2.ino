// Libreria de WiFi
#include <WiFi.h>

// SSID y contraseña
const char* ssid = "CASA-2.4";
const char* password =  "abcde12345";

// Establecer el número de puerto del servidor web en 80
WiFiServer server(80);

// Variable para almacenar la solicitud HTTP
String header;

// Variables auxiliares para almacenar el estado de salida actual
String output26State = "off";
String output27State = "off";

// Salidas GPIO
const int output26 = 26;
//const int output27 = 27;

// Tiempo actual
unsigned long currentTime = millis();
// Tiempo previo
unsigned long previousTime = 0; 
// Tiempo de espera
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  // Declarar variables como salida
  pinMode(output26, OUTPUT);
//  pinMode(output27, OUTPUT);
 
  digitalWrite(output26, LOW);
//  digitalWrite(output27, LOW);

  // Conectarse al WiFi con SSID y contraseña
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Se imprime IP
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Clientes entrantes

  if (client) {                             // Si un nuevo cliente se conecta,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // imprime un mensaje en el puerto serie
    String currentLine = "";                // hacer una cadena para contener los datos entrantes del cliente
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {             // Si hay bytes para leer del cliente,
        char c = client.read();             // leer un byte, luego
        Serial.write(c);                    // imprímir en el monitor de serie
        header += c;
        if (c == '\n') {                    // si el byte es un carácter de nueva línea
          // si la línea actual está en blanco, tiene dos caracteres de nueva línea seguidos.
          // ese es el final de la solicitud HTTP del cliente, así que envíe una respuesta:
          
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // enciende y apaga el LED
            if (header.indexOf("GET /26/on") >= 0) 
            {
              Serial.println("GPIO 26 on");
              output26State = "Encendido";
              digitalWrite(output26, HIGH);
            } 
            
            else if (header.indexOf("GET /26/off") >= 0) 
            {
              Serial.println("GPIO 26 off");
              output26State = "Apagado";
              digitalWrite(output26, LOW);
            } 
            
            // Mostrar la página web HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            
            // CSS para diseñar los botones de encendido / apagado
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Encabezado de la página web
            client.println("<body><h1>ESP32 Servidor Web</h1>");
            
            // Muestra el estado actual y los botones ON / OFF para GPIO 26
            client.println("<p>GPIO 26 - ESTADO: " + output26State + "</p>");
            // Si output26State está apagado, muestra el botón ON     
            if (output26State=="Apagado") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            client.println("</body></html>");
            // La respuesta HTTP termina con otra línea en blanco
            client.println();
            // Salir del bucle while
            break;
          } else { // si tiene una nueva línea, borre currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;  
        }
      }
    }
    // Borrar la variable de encabezado
    header = "";
    // Cerrar la conexión
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}
