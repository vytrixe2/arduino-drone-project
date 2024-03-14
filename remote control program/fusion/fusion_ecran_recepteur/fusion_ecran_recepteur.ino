//écran
#include <LiquidCrystal.h>
//récepteur
#include <SPI.h>
#include <RFM69.h>

#define NODEID 2 // Identifiant unique de ce nœud
#define NETWORKID 100 // Identifiant de réseau
#define TRANSMITTERID 1 // Identifiant de l'émetteur

#define FREQUENCY RF69_433MHZ // Fréquence de fonctionnement
#define ENCRYPTKEY "MPU6050" // Clé de chiffrement

RFM69 radio;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void setup() {
Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20);
}

void loop() {
  if (radio.receiveDone()) {
    // Vérifier si les données reçues proviennent de l'émetteur
    if (radio.SENDERID == TRANSMITTERID) {
      // Récupérer les données du joystick
      struct JoystickData {
        int x;
        int y;
        int z;
      } data;
      
      memcpy(&data, (void*)radio.DATA, sizeof(data));

      lcd.setCursor(0,0);
      lcd.write("Déplacement x :");
      lcd.write(data.x);
      lcd.setCursor(0,1);
      lcd.write("Déplacement y :");
      lcd.write(data.y);
      lcd.setCursor(0, 2);
      lcd.write("Chute :");
      lcd.write(data.z);
    }
  }
}
