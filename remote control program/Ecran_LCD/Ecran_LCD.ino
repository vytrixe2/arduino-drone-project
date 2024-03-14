#include <LiquidCrystal.h>

// Définir les dimensions du pixel art du drone
const int droneWidth = 16;
const int droneHeight = 8;

// Définir le pixel art du drone
const byte drone[droneHeight] = {
  B00000000,
  B01111110,
  B11000011,
  B10000001,
  B10100101,
  B10000001,
  B01111110,
  B00000000
};

// Broches pour l'écran LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialisation de l'écran LCD
  lcd.begin(16, 2);
  // Affichage du pixel art du drone
  displayDrone();
}

void loop() {
  // Le programme principal n'a pas besoin de faire quelque chose de continu
}

void displayDrone() {
  // Afficher chaque ligne du pixel art du drone sur l'écran LCD
  for (int y = 0; y < droneHeight; y++) {
    lcd.setCursor(0, y);
    // Afficher la ligne du pixel art
    lcd.write(drone[y]);
  }
}
