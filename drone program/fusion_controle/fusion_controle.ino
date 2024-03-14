#include <SPI.h>
#include <RFM69.h>
#include <Servo.h>

#define NODEID 2
#define NETWORKID 100
#define TRANSMITTERID 1
#define FREQUENCY RF69_433MHZ
#define ENCRYPTKEY "droneMathis"

#define MOTOR_MIN 1000
#define MOTOR_MAX 2000

RFM69 radio;
Servo motorA;
Servo motorB;
Servo motorC;
Servo motorD;

float vitesse_stable = 232.054730983302;

struct Commande {
  int x1;
  int y1;
  int x2;
  int y2;
} data;
void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20);

  motorA.attach(3);
  motorB.attach(5);
  motorC.attach(6);
  motorD.attach(9);
}
void loop() {
  if (radio.receiveDone()) {
    if (radio.SENDERID == 1) {
      data = *(struct Commande*)radio.DATA;
      if (data.x1 > 0) {
        rotation_antihoraire();
      } else if (data.x1 < 0) {
        rotation_horaire();
      }
      if (data.x2 > 0) {
        avancer_gauche();
      } else if (data.x2 < 0) {
        avancer_droite();
      }
      if (data.y1 > 0) {
        avancer();
      } else if (data.y1 < 0) {
        reculer();
      }
      if (data.y2 > 0) {
        monter();
      } else if (data.y2 < 0) {
        descendre();
      } else {
        stable();
      }
    }
  }
}
void stable() {
  motorA.writeMicroseconds(vitesse_stable);
  motorB.writeMicroseconds(vitesse_stable);
  motorC.writeMicroseconds(vitesse_stable);
  motorD.writeMicroseconds(vitesse_stable);
}
void monter() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y2));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y2));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y2));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y2));
}
void descendre() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y2)));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y2)));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y2)));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y2)));
}
void avancer() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y1));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y1));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y1));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.y1));
}
void reculer() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y1)));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y1)));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y1)));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.y1)));
}
void avancer_gauche() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x1));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x1));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x1));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x1));
}
void avancer_droite() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x1)));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x1)));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x1)));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x1)));
}
void rotation_horaire() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x2)));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x2)));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x2)));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * (-data.x2)));
}
void rotation_antihoraire() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x2));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x2));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x2));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.229452690167 * data.x2));
}