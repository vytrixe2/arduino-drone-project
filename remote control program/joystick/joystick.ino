const int joystick1_x_pin = A0; // Joystick 1 axe X
const int joystick1_y_pin = A1; // Joystick 1 axe Y
const int joystick2_x_pin = A2; // Joystick 2 axe X
const int joystick2_y_pin = A3; // Joystick 2 axe Y

void setup() {
  Serial.begin(9600);
}

void loop() {
  int joystick1_x = analogRead(joystick1_x_pin);
  int joystick1_y = analogRead(joystick1_y_pin);
  int joystick2_x = analogRead(joystick2_x_pin);
  int joystick2_y = analogRead(joystick2_y_pin);

  // Convertir les valeurs analogiques en pourcentage
  float joystick1_x_percent = map(joystick1_x, 0, 1023, -100, 100);
  float joystick1_y_percent = map(joystick1_y, 0, 1023, -100, 100);
  float joystick2_x_percent = map(joystick2_x, 0, 1023, -100, 100);
  float joystick2_y_percent = map(joystick2_y, 0, 1023, -100, 100);

  // Afficher les valeurs sur le port série
  Serial.print("Joystick 1 - Axe X: ");
  Serial.print(joystick1_x_percent);
  Serial.print("%, Axe Y: ");
  Serial.print(joystick1_y_percent);
  Serial.print("%, Force: ");
  Serial.println(sqrt(pow(joystick1_x_percent, 2) + pow(joystick1_y_percent, 2)));

  Serial.print("Joystick 2 - Axe X: ");
  Serial.print(joystick2_x_percent);
  Serial.print("%, Axe Y: ");
  Serial.print(joystick2_y_percent);
  Serial.print("%, Force: ");
  Serial.println(sqrt(pow(joystick2_x_percent, 2) + pow(joystick2_y_percent, 2)));

  delay(100); // Délai pour éviter le spam du port série
}
