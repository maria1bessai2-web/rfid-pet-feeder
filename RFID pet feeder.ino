#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ================= RFID CONFIGURATION =================
// Bibliothèque SPI : communication avec le module RFID
// MFRC522 : lecteur RFID utilisé pour lire les tags
#define SS_PIN 10   // Pin de sélection du module RFID
#define RST_PIN 9   // Pin de reset du module RFID

MFRC522 rfid(SS_PIN, RST_PIN); // Création de l'objet RFID

// ================= SERVO MOTOR =================
// Servo utilisé pour ouvrir/fermer le distributeur de nourriture
Servo feederServo;
const int servoPin = 6; // Pin de contrôle du servo

// Positions du servo
int closedPos = 0;   // position fermée du distributeur
int openPos = 90;    // position ouverte pour laisser tomber la nourriture

// ================= AUTHORIZED RFID TAG =================
// UID autorisé (collier de l’animal reconnu)
String allowedUID = "3A9F2144";

// ================= SETUP FUNCTION =================
// Fonction exécutée une seule fois au démarrage
void setup() {
  Serial.begin(9600); // Initialisation du moniteur série

  SPI.begin();        // Démarrage de la communication SPI
  rfid.PCD_Init();    // Initialisation du lecteur RFID

  feederServo.attach(servoPin); // Connexion du servo au pin défini
  feederServo.write(closedPos);  // Assurer que le distributeur est fermé au départ

  Serial.println("RFID Feeding System Ready...");
}

// ================= MAIN LOOP =================
// Fonction principale exécutée en boucle
void loop() {

  // Vérifie si une nouvelle carte RFID est détectée
  if (!rfid.PICC_IsNewCardPresent()) return;

  // Vérifie si la carte peut être lue correctement
  if (!rfid.PICC_ReadCardSerial()) return;

  // Lecture de l'UID de la carte
  String uid = "";

  // Conversion des bytes UID en format lisible HEX
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  uid.toUpperCase(); // Uniformisation en majuscules

  Serial.print("Detected UID: ");
  Serial.println(uid);

  // ================= DECISION LOGIC =================
  // Vérifie si l'UID correspond à un animal autorisé
  if (uid == allowedUID) {

    Serial.println("Authorized animal detected → Dispensing food");

    giveFood(); // Activation du distributeur

  } else {

    Serial.println("Unauthorized animal → Access denied");
  }

  // Fin de communication avec la carte RFID
  rfid.PICC_HaltA();
}

// ================= FOOD DISPENSING FUNCTION =================
// Cette fonction contrôle le mécanisme de distribution
void giveFood() {

  // Ouvre le distributeur
  feederServo.write(openPos);

  // Temps nécessaire pour laisser tomber la nourriture
  delay(2000);

  // Referme le distributeur
  feederServo.write(closedPos);

  // Pause de sécurité avant la prochaine activation
  delay(1000);
}
