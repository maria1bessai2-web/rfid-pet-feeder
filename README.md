#  RFID Pet Feeder - Distributeur Automatique de Nourriture

##  Description
Ce projet consiste à concevoir et réaliser un distributeur automatique de nourriture pour animaux utilisant la technologie RFID.

Le système permet d’identifier un animal grâce à un tag RFID et de lui distribuer automatiquement une portion de nourriture adaptée.

##  Objectifs
- Automatiser l’alimentation des animaux
- Identifier chaque animal via RFID
- Distribuer des portions personnalisées
- Assurer un contrôle d’accès sécurisé

## Technologies utilisées
- Arduino Uno
- Module RFID (MFRC522)
- Servomoteur
- Capteur DHT22
- Relais
- Afficheur LCD
- Arduino IDE

##  Fonctionnement
1. L’animal s’approche avec son tag RFID
2. Le module RFID lit l’identifiant
3. Arduino vérifie l’autorisation
4. Le servomoteur distribue la nourriture
5. Les données peuvent être affichées sur LCD

##  Architecture du système
- Acquisition : RFID + capteurs
- Traitement : Arduino
- Action : Servomoteur + relais
- Interface : LCD

##  Résultats
- Identification rapide et fiable
- Distribution précise des portions
- Fonctionnement automatique validé

##  Améliorations possibles
- Ajout d’une application mobile
- Suivi des repas en temps réel
- Connexion IoT (WiFi / Cloud)
- Caméra de surveillance

##  Auteur
- Maria Bessai

##  Licence
Projet académique 2023/2024
