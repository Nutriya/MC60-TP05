#define BLYNK_TEMPLATE_ID "TMPL5037QLVnF"                     // ID du modèle Blynk
#define BLYNK_TEMPLATE_NAME "uwu"                             // Nom du modèle Blynk
#define BLYNK_AUTH_TOKEN "izwoM5CCikaAlmDQGJ2MBbuyXl4XeUiH"   // Token d'authentification Blynk
#define BLYNK_PRINT Serial                                    // Définir la sortie de débogage sur le port série

#include <WiFi.h>                                             // Bibliothèque pour la connexion WiFi
#include <BlynkSimpleEsp32.h>                                 // Bibliothèque Blynk pour ESP32
#include <Adafruit_Sensor.h>                                  // Bibliothèque de capteurs Adafruit
#include <Adafruit_BME280.h>                                  // Bibliothèque pour le capteur BME280
#include <Ticker.h>                                           // Bibliothèque pour les minuteries


char ssid[] = "Galaxy A13B7E0";                               // SSID du réseau WiFi
char pass[] = "txeh8505";                                     // Mot de passe du réseau WiFi

Adafruit_BME280 bme;                                          // Création d'une instance pour le capteur BME280 (I2C)

Ticker timer;                                                 // Création d'une instance de minuterie

// Fonction pour lire les données du capteur
void readSensor() {
  float temperature = bme.readTemperature();        // Lire la température
  float pressure = bme.readPressure() / 100.0F;     // Lire la pression et convertir en hPa
  float humidity = bme.readHumidity();              // Lire l'humidité

  // Afficher les valeurs lues sur le port série
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %\n");

  // Envoyer les données aux widgets virtuels Blynk
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V0, pressure);
  Blynk.virtualWrite(V3, humidity);
}

void setup() {
  Serial.begin(115200);                         // Initialiser la communication série à 115200 bauds
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);    // Connexion à Blynk avec le token et les informations WiFi

  unsigned status = bme.begin(0x76);            // Initialiser le capteur BME280 à l'adresse I2C 0x76
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");    // Message d'erreur si le capteur n'est pas trouvé
    while (1) delay(10);                                                                          // Boucle infinie en cas d'erreur
  }

  // Configurer la minuterie pour appeler readSensor toutes les 2 secondes
  timer.attach(2, readSensor);

  Serial.println("-- BME280 Test --");    // Message de démarrage
}

void loop() {
  Blynk.run();    // Exécuter Blynk
}