#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <RFM69.h>
#include <Servo.h>

#define NODEID 2
#define NETWORKID 100
#define RECEIVERID 1
#define TRANSMITTERID 1
#define FREQUENCY RF69_433MHZ
#define ENCRYPTKEY "droneMathis"

#define MOTOR_MIN 1000
#define MOTOR_MAX 2000

Adafruit_MPU6050 mpu;
RFM69 radio;
Servo motorA;
Servo motorB;
Servo motorC;
Servo motorD;

float vitesse_stable = 232.054730983302;

const int maxAcc = 16384;  // Valeur maximale pour l'accélération (MPU6050)
const int minAcc = -16384;  // Valeur minimale pour l'accélération (MPU6050)
const int maxGyro = 32767;  // Valeur maximale pour la rotation (MPU6050)
const int minGyro = -32767; // Valeur minimale pour la rotation (MPU6050)

struct Commande {
  int x1;
  int y1;
  int x2;
  int y2;
} data;

struct Mpu6050 {
  int ax;
  int ay;
  int az;
  int rx;
  int ry;
  int rz;
};
void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20);

  motorA.attach(0);
  motorB.attach(3);
  motorC.attach(4);
  motorD.attach(5);
  Serial.println(F("Initialize System"));
  if (!mpu.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
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
  sensors_event_t a, g, temp;
 	mpu.getEvent(&a, &g, &temp);
  Mpu6050 data;
data.ax = map(a.acceleration.x, minAcc, maxAcc, 0, 100);
data.ay = map(a.acceleration.y, minAcc, maxAcc, 0, 100);
data.az = map( a.acceleration.z, minAcc, maxAcc, 0, 100);
data.rx = map(g.gyro.x, minGyro, maxGyro, 0, 100); 
data.ry = map(g.gyro.y, minGyro, maxGyro, 0, 100);
data.rz = map(g.gyro.z, minGyro, maxGyro, 0, 100);

  if (radio.sendWithRetry(RECEIVERID, &data, sizeof(data))) {
    Serial.println("Transmission réussie !");
  } else {
    Serial.println("Erreur lors de la transmission !");
  }
  
  delay(100); 
}
//0,17945269016698 +
//2,32054730983302 -
void stable() {
  motorA.writeMicroseconds(vitesse_stable);
  motorB.writeMicroseconds(vitesse_stable);
  motorC.writeMicroseconds(vitesse_stable);
  motorD.writeMicroseconds(vitesse_stable);
}
void monter() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y2));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y2));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y2));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y2));
}
void descendre() {
  motorA.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y2)));
  motorB.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y2)));
  motorC.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y2)));
  motorD.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y2)));
}
void avancer() {
  motorA.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.y1));
  motorB.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.y1));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y1));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.y1));
}
void reculer() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.y1)));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.y1)));
  motorC.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y1)));
  motorD.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.y1)));
}
void avancer_gauche() {
  motorA.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.x1));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.x1));
  motorC.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.x1));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.x1));
}
void avancer_droite() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.x1)));
  motorB.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.x1)));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.x1)));
  motorD.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.x1)));
}
void rotation_horaire() {
  motorA.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.x2)));
  motorB.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.x2)));
  motorC.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * (-data.x2)));
  motorD.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * (-data.x2)));
}
void rotation_antihoraire() {
  motorA.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.x2));
  motorB.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.x2));
  motorC.writeMicroseconds(vitesse_stable + (int)(0.17945269016698 * data.x2));
  motorD.writeMicroseconds(vitesse_stable - (int)(2.32054730983302 * data.x2));
}