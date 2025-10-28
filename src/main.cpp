#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <ESP32Servo.h>
#include <SPIFFS.h>

// ---------------------------
// 🔹 1. Paramètres WiFi
// ---------------------------
const char* ssid = "RAZAFY";
const char* password = "123456789"; // mot de passe du WiFi AP

// ---------------------------
// 🔹 2. Initialisation des objets
// ---------------------------
AsyncWebServer server(80);  // Création du serveur web sur le port 80
Servo myServo;              // Création de l’objet servo
const int servoPin = 13;    // Broche de signal PWM
int servoAngle = 0;         // Position actuelle du servo

// ---------------------------
// 🔹 3. Fonction setup()
// ---------------------------
void setup() {
  Serial.begin(115200);
  Serial.println();

  // ---------------------------
  // Monter SPIFFS
  // ---------------------------
  if(!SPIFFS.begin(true)){   // true : crée le système de fichiers si absent
      Serial.println("Erreur : SPIFFS n'a pas pu être monté !");
      return;
  }
  Serial.println("SPIFFS monté avec succès !");

  // ---------------------------
  // Configuration du Servo
  // ---------------------------
  myServo.attach(servoPin);
  myServo.write(0); // Position initiale

  // ---------------------------
  // Création du WiFi Access Point
  // ---------------------------
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP créé !");
  Serial.print("Nom du réseau : ");
  Serial.println(ssid);
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.softAPIP());

  // ---------------------------
  // 🔹 4. Routes du serveur web
  // ---------------------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/style.css", SPIFFS, "/style.css");
  server.serveStatic("/script.js", SPIFFS, "/script.js");

  server.on("/open", HTTP_GET, [](AsyncWebServerRequest *request){
    myServo.write(90);
    servoAngle = 90;
    Serial.println("Barrière ouverte !");
    request->send(200, "text/plain", "OPENED");
  });

  server.on("/close", HTTP_GET, [](AsyncWebServerRequest *request){
    myServo.write(0);
    servoAngle = 0;
    Serial.println("Barrière fermée !");
    request->send(200, "text/plain", "CLOSED");
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request){
    String status = (servoAngle == 90) ? "OPEN" : "CLOSED";
    request->send(200, "text/plain", status);
  });

  // ---------------------------
  // 🔹 5. Démarrage du serveur
  // ---------------------------
  server.begin();
  Serial.println("Serveur Web démarré !");
}

// ---------------------------
// 🔹 6. Boucle principale
// ---------------------------
void loop() {
  // Pas besoin de code ici, tout est géré par AsyncWebServer
}
