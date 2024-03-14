#include <SPI.h>
#include <RFM69.h>

#define NODEID 2 // Identifiant unique de ce nœud
#define NETWORKID 100 // Identifiant de réseau
#define TRANSMITTERID 1 // Identifiant de l'émetteur

#define FREQUENCY RF69_433MHZ // Fréquence de fonctionnement
#define ENCRYPTKEY "sampleEncryptKey" // Clé de chiffrement

RFM69 radio;

void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  
  if (!radio.setPowerLevel(20)) {
    Serial.println("Erreur lors du réglage de la puissance de transmission !");
  }
}

void loop() {
  if (radio.receiveDone()) {
    // Vérifier si les données reçues proviennent de l'émetteur
    if (radio.SENDERID == TRANSMITTERID) {
      // Récupérer les données du joystick
      struct JoystickData {
        int x;
        int y;
      } data;
      
      memcpy(&data, (void*)radio.DATA, sizeof(data));
      
      // Afficher les valeurs sur le moniteur série
      Serial.print("Valeur X: ");
      Serial.print(data.x);
      Serial.print("\t Valeur Y: ");
      Serial.println(data.y);
    }
  }
}
