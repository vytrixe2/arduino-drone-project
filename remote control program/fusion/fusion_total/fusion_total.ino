#include <SPI.h>
#include <RFM69.h>
#include <LiquidCrystal.h>

// Définition des constantes pour le nœud, le réseau, le récepteur, la fréquence et la clé de chiffrement
#define NODEID1 1 // Identifiant unique de ce nœud
#define NETWORKID 100 // Identifiant de réseau
#define RECEIVERID 2 // Identifiant du récepteur
#define FREQUENCY RF69_433MHZ // Fréquence de fonctionnement
#define ENCRYPTKEY "droneMathis" // Clé de chiffrement

RFM69 radio; // Initialisation de l'objet RFM69
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Initialisation de l'écran LCD

// Définition des broches pour les joysticks
const int joystick1_x_pin = A0; // Joystick 1 axe X
const int joystick1_y_pin = A1; // Joystick 1 axe Y
const int joystick2_x_pin = A2; // Joystick 2 axe X
const int joystick2_y_pin = A3; // Joystick 2 axe Y

void setup() {
  Serial.begin(9600); // Initialisation de la communication série
  radio.initialize(FREQUENCY, NODEID1, NETWORKID); // Initialisation du module RFM69
  radio.encrypt(ENCRYPTKEY); // Activation du chiffrement avec la clé spécifiée
  radio.setPowerLevel(20); // Réglage de la puissance de transmission
  lcd.begin(16, 2); // Initialisation de l'écran LCD avec 16 colonnes et 2 lignes
}

void loop() {
  // Lecture des valeurs des joysticks et conversion en pourcentage
  int joystick1_x = analogRead(joystick1_x_pin);
  int joystick1_y = analogRead(joystick1_y_pin);
  int joystick2_x = analogRead(joystick2_x_pin);
  int joystick2_y = analogRead(joystick2_y_pin);
  float joystick1_x_percent = map(joystick1_x, 0, 1023, -100, 100);
  float joystick1_y_percent = map(joystick1_y, 0, 1023, -100, 100);
  float joystick2_x_percent = map(joystick2_x, 0, 1023, -100, 100);
  float joystick2_y_percent = map(joystick2_y, 0, 1023, -100, 100);

  // Structure de données pour les valeurs des joysticks
  struct Joystick1data {
    int x1;
    int y1;
    int x2;
    int y2;
  };

  // Remplissage des données des joysticks dans la structure
  Joystick1data data;
  data.x1 = joystick1_x_percent;
  data.y1 = joystick1_y_percent;
  data.x2 = joystick2_x_percent;
  data.y2 = joystick2_y_percent;

  // Envoi des données des joysticks au récepteur
  if (radio.sendWithRetry(RECEIVERID, &data, sizeof(data))) {
    Serial.println("Transmission réussie !");
  } 
  else {
    Serial.println("Erreur lors de la transmission !");
  }

  // Réception des données du joystick sur le récepteur et affichage sur l'écran LCD
  if (radio.receiveDone()) {
    if (radio.SENDERID == 1) { // Assuming transmitter ID is 1
      struct JoystickData {
        int x;
        int y;
        int z;
      } received_data;
      
      memcpy(&received_data, (void*)radio.DATA, sizeof(received_data));

      lcd.setCursor(0,0);
      lcd.print("Déplacement x :");
      lcd.print(received_data.x);
      lcd.setCursor(0,1);
      lcd.print("Déplacement y :");
      lcd.print(received_data.y);
      lcd.setCursor(0, 2);
      lcd.print("Chute :");
      lcd.print(received_data.z);
    }
  }

  delay(100); // Délai pour éviter la surcharge du processeur
}
