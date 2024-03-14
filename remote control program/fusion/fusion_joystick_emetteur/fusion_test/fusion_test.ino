//RFM69
#include <SPI.h>
#include <RFM69.h>

#define NODEID 1 // Identifiant unique de ce nœud
#define NETWORKID 100 // Identifiant de réseau
#define RECEIVERID 2 // Identifiant du récepteur

#define FREQUENCY RF69_433MHZ // Fréquence de fonctionnement
#define ENCRYPTKEY "droneMathis" // Clé de chiffrement

RFM69 radio;
//joystick
const int joystick1_x_pin = A0; // Joystick 1 axe X
const int joystick1_y_pin = A1; // Joystick 1 axe Y
const int joystick2_x_pin = A2; // Joystick 2 axe X
const int joystick2_y_pin = A3; // Joystick 2 axe Y

void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20); // Réglage de la puissance de transmission
}


void loop() {
  int joystick1_x = analogRead(joystick1_x_pin);
  int joystick1_y = analogRead(joystick1_y_pin);
  int joystick2_x = analogRead(joystick2_x_pin);
  int joystick2_y = analogRead(joystick2_y_pin);

  float joystick1_x_percent = map(joystick1_x, 0, 1023, -100, 100);
  float joystick1_y_percent = map(joystick1_y, 0, 1023, -100, 100);
  float joystick2_x_percent = map(joystick2_x, 0, 1023, -100, 100);
  float joystick2_y_percent = map(joystick2_y, 0, 1023, -100, 100);

  struct Joystick1data {
    int x1;
    int y1;
    int x2;
    int y2;
  };

  Joystick1data data;
  data.x1 = joystick1_x_percent;
  data.y1 = joystick1_y_percent;
  data.x2 = joystick2_x_percent;
  data.y2 = joystick2_y_percent;

  if (radio.sendWithRetry(RECEIVERID, &data, sizeof(data))) {
    Serial.println("Transmission réussie !");
  } 
  else {
    Serial.println("Erreur lors de la transmission !");
  }

  delay(100);
}
