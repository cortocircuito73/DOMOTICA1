//INCLUIR LIBRERIA WIFI
#include <ESP8266WiFi.h>

// VARIABLES DE RED
const char SSID_AP[] = "ESP8266-AP"; //NOMBRE DE LA RED
const char PASS_AP[] = "";  //CONTRASEÑA

WiFiServer server(80); // PUERTO DEL SERVIDOR

// CODIGO HTML 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String tit = "<!DOCTYPE html><html><head><title>PRUEBA LED</title></head><body><div id='main'><h2>PRUEBA LED ESP8266</h2>";
String bot_1 = "<form id='F1' action='LED_ON'><input class='button' type='submit' value='ON' ></form><br>";
String bot_2 = "<form id='F2' action='LED_OFF'><input class='button' type='submit' value='OFF' ></form><br>";
String fin = "</div></body></html>";
 
String pet = ""; //PETICIONES AL SERVIDOR

// VARIABLES PARA SALIDAS DEL ESP8266
int LED = 15;
 
void setup() {
  //VELOCIDAD DEL PUERTO SERIAL
  Serial.begin(115200);
  
  //DEFINICION DE SALIDAS
  pinMode(LED, OUTPUT);

  //CONFIGURACION DE LA RED
  WiFi.mode(WIFI_AP); //MODO ACCESS POINT
  delay(200);

  //INICIO DE LA RED
  WiFi.softAP(SSID_AP,PASS_AP);

  //ENCABEZADO DEL PUERTO SERIAL
  Serial.println("RED CREADA EN MODO ACCESS POINT");
  Serial.println("\n");
  Serial.print("NOMBRE DE LA RED: ");
  Serial.print(SSID_AP);
  Serial.print("\nIP: ");
  Serial.print(WiFi.softAPIP()); //IP LOCAL DE LA ESP8266
  Serial.println("\n**********************************************");
  
  server.begin(); //INICIAR SERVIDOR
} 
 
 
void loop() 
{
  //VERIFICAR SI EL SERVIDOR RECIBE UNA CONEXION
  WiFiClient client = server.available();
  if (!client){return;}

  // LEE LAS PETICIONES
  pet = client.readStringUntil('\r');
  Serial.println(pet);

  // CONDICIONALES DE LAS PETICIONES
  if      (pet.indexOf("LED_ON")>0) {Serial.println("LED ENCENDIDO"); digitalWrite(LED,1);}
  else if (pet.indexOf("LED_OFF")>0){Serial.println("LED APAGADO"); digitalWrite(LED,0);}

  //VISTA DEL LADO DEL CLIENTE
  client.flush();
  client.print(header);
  client.print(tit);
  client.print(bot_1);
  client.print(bot_2);
  client.print(fin);

  //RETARDO ENTRE PETICIONES
  delay(10);
 
} 
