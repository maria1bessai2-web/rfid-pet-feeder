#include "thingProperties.h"
#include <DHT.h>
#include <DHT_U.h>

// ================= CONFIGURATION =================

// Capteur DHT22
#define DHTPIN 12
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Relais
const int relayPin = 14;

// ================= SETUP =================

void setup() {
  Serial.begin(9600);

  // Initialisation relais
  pinMode(relayPin, OUTPUT);

  // Initialisation capteur
  dht.begin();

  // Initialisation Arduino Cloud
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

// ================= LOOP =================

void loop() {
  ArduinoCloud.update();

  readDHT();
  controlAutoMode();
}

// ================= FONCTIONS =================

// Contrôle manuel relais
void onRelaySwitchChange() {
  if (relay_switch) {
    digitalWrite(relayPin, LOW);  // OFF
  } else {
    digitalWrite(relayPin, HIGH); // ON
  }
}

// Lecture capteur DHT
void readDHT() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(hum) || isnan(temp)) {
    Serial.println("Erreur lecture DHT !");
    return;
  }

  humidity = hum;
  temperature = temp;

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(1000);
}

// Mode automatique
void controlAutoMode() {
  if (autoChange) {
    if (temperature >= 30 || humidity >= 70) {
      digitalWrite(relayPin, LOW);   // OFF
    } else {
      digitalWrite(relayPin, HIGH);  // ON
    }
  } else {
    onRelaySwitchChange();
  }
}