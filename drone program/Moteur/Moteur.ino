#include <Servo.h>

#define MOTOR_MIN 1000 // Valeur minimale du signal PWM
#define MOTOR_MAX 2000 // Valeur maximale du signal PWM

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void setup() {
  motor1.attach(3); // Broche PWM pour le premier ESC
  motor2.attach(5); // Broche PWM pour le deuxième ESC
  motor3.attach(6); // Broche PWM pour le troisième ESC
  motor4.attach(9); // Broche PWM pour le quatrième ESC
}

void loop() {
  // Contrôle du premier moteur
  motor1.writeMicroseconds(MOTOR_MIN); // Vitesse minimale
  delay(1000);
  motor1.writeMicroseconds(MOTOR_MAX); // Vitesse maximale
  delay(1000);

  // Contrôle du deuxième moteur
  motor2.writeMicroseconds(MOTOR_MIN); // Vitesse minimale
  delay(1000);
  motor2.writeMicroseconds(MOTOR_MAX); // Vitesse maximale
  delay(1000);

  // Contrôle du troisième moteur
  motor3.writeMicroseconds(MOTOR_MIN); // Vitesse minimale
  delay(1000);
  motor3.writeMicroseconds(MOTOR_MAX); // Vitesse maximale
  delay(1000);

  // Contrôle du quatrième moteur
  motor4.writeMicroseconds(MOTOR_MIN); // Vitesse minimale
  delay(1000);
  motor4.writeMicroseconds(MOTOR_MAX); // Vitesse maximale
  delay(1000);
}
