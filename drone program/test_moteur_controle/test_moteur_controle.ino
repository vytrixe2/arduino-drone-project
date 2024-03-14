-*#include <Servo.h>
#define MOTOR_MIN 1000 // Valeur minimale du signal PWM
#define MOTOR_MAX 2000 // Valeur maximale du signal PWM

Servo motorA;
Servo motorB;
Servo motorC;
Servo motorD;

int vitesse_stable = 232.054730983302
void setup() {
  motorA.attach(1);
  motorB.attach(2);
  motorC.attach(3);
  motorD.attach(4);

}

void loop() {


}

void stable(){
  analogWrite(motorA, vitesse_stable); // Contrôle du moteur A
  analogWrite(motorB, vitesse_stable); // Contrôle du moteur B
  analogWrite(motorC, vitesse_stable); // Contrôle du moteur C
  analogWrite(motorD, vitesse_stable); // Contrôle du moteur D
}

void monter(){
  int vitesse_monter = ( vitesse_stable + (0,229452690167 * data.y2));
analogWrite(motorA, vitesse_monter); // Contrôle du moteur A
analogWrite(motorB, vitesse_monter); // Contrôle du moteur B
analogWrite(motorC, vitesse_monter); // Contrôle du moteur C
analogWrite(motorD, vitesse_monter); // Contrôle du moteur D
}

void descendre (){
  int vitesse_descente = ( vitesse_stable - (2,32054730983 * (-data.y2)));
  analogWrite(motorA, vitesse_descente);
  analogWrite(motorB, vitesse_descente);
  analogWrite(motorC, vitesse_descente);
  analogWrite(motorD, vitesse_descente); 
}

void avancer() {
  int vitesse_avant = ( vitesse_stable - (2,32054730983 * data.y1));
  int vitesse_arrière = (vitesse_stable + (0,229452690167 * data.y1));
  analogWrite(motorA, vitesse_avant);
  analogWrite(motorB, vitesse_avant);
  analogWrite(motorC, vitesse_arrière);
  analogWrite(motorD, vitesse_arrière); 
}

void reculer (){
  int vitesse_arrière = (vitesse_stable + (0,229452690167 * (-data.y1)));
  int vitesse_avant = ( vitesse_stable - (2,32054730983 * (-data.y1)));
  analogWrite(motorA, vitesse_arrière);
  analogWrite(motorB, vitesse_arrière);
  analogWrite(motorC, vitesse_avant);
  analogWrite(motorD, vitesse_avant); 
}

void avancer_gauche (){
  analogWrite(motorA, (vitesse_stable - 2,32054730983 * (data.x1)));
  analogWrite(motorB, (vitesse_stable + (0,229452690167 * (data.x1))));
  analogWrite(motorC, (vitesse_stable - 2,32054730983 * (data.x1)));
  analogWrite(motorD, (vitesse_stable + (0,229452690167 * (data.x1)))); 
}

void avancer_droite() {
analogWrite(motorA, (vitesse_stable + (0,229452690167 * (-data.x1))));
analogWrite(motorB, (vitesse_stable - 2,32054730983 * (-data.x1)));
analogWrite(motorC, (vitesse_stable + (0,229452690167 * (-data.x1))));
analogWrite(motorD, (vitesse_stable - 2,32054730983 * (-data.x1))); 
}

void rotation_horaire(){
analogWrite(motorA, (vitesse_stable + (0,229452690167 * (-data.x2))));
analogWrite(motorB, (vitesse_stable - 2,32054730983 * (-data.x2)));
analogWrite(motorC, (vitesse_stable - 2,32054730983 * (-data.x2)));
analogWrite(motorD, (vitesse_stable + (0,229452690167 * (-data.x2)))); 
}
void rotation_antihoraire(){
analogWrite(motorA, (vitesse_stable - 2,32054730983 * (-data.x2)));
analogWrite(motorB, (vitesse_stable + (0,229452690167 * (-data.x2))));
analogWrite(motorC, (vitesse_stable + (0,229452690167 * (-data.x2))));
analogWrite(motorD, (vitesse_stable - 2,32054730983 * (-data.x2))); 
}