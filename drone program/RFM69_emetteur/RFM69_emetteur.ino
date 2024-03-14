#include <SPI.h>
#include <RFM69.h>

#define NODEID 1 // Identifiant unique de ce nœud
#define NETWORKID 100 // Identifiant de réseau
#define RECEIVERID 2 // Identifiant du récepteur

#define FREQUENCY RF69_433MHZ // Fréquence de fonctionnement
#define ENCRYPTKEY "sampleEncryptKey" // Clé de chiffrement

RFM69 radio;

void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20);
}

void loop() {
  // Lire les entrées du joystick
  int x_axis = analogRead(A0);
  int y_axis = analogRead(A1);
  
  // Créer une structure de données pour les valeurs
  struct JoystickData {
    int x;
    int y;
  };
  
  JoystickData data;
  data.x = map(x_axis, 0, 1023, 0, 255); // Mapper la plage des valeurs de 0 à 1023 à 0 à 255
  data.y = map(y_axis, 0, 1023, 0, 255);
  
  // Envoyer les données au récepteur
  if (radio.sendWithRetry(RECEIVERID, &data, sizeof(data))) {
    Serial.println("Transmission réussie !");
  } else {
    Serial.println("Erreur lors de la transmission !");
  }
  
  delay(100); // Attendre un peu entre les transmissions
}
