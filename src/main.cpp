#define BLYNK_TEMPLATE_ID "TMPL50tqVtMOD"
#define BLYNK_TEMPLATE_NAME "TP05"
#define BLYNK_AUTH_TOKEN "_CTMEaNoUcOlmPWbtNMxcqCoa-ASjeIR"
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Ticker.h>

#define SEALEVELPRESSURE_HPA (1013.25)



char ssid[] = "Galaxy A13B7E0";
char pass[] = "txeh8505";

Adafruit_BME280 bme; // I2C

Ticker timer;

void readSensor() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  float humidity = bme.readHumidity();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, pressure);
  Blynk.virtualWrite(V3, altitude);
  Blynk.virtualWrite(V4, humidity);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  unsigned status = bme.begin(0x76); // Adresse I2C par défaut du BME280
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    while (1) delay(10);
  }

  // Setup timer to call readSensor every 2 seconds
  timer.attach(2, readSensor);

  Serial.println("-- BME280 Test --");
}

void loop() {
  Blynk.run();
}