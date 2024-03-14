//MPU6050
#include<Wire.h>
#include<Adafruit_MPU6050.h>
#include<Adafruit_Sensor.h>
//émetteur
#include<SPI.h>
#include<RFM69.h>

#define NODEID 2
#define NETWORKID 100
#define RECEIVERID 1

#define FREQUENCY RF69_433MHZ
#define ENCRYPTKEY "droneMathis"

RFM69 radio;

Adafruit_MPU6050 mpu;

const int maxAcc = 16384;  // Valeur maximale pour l'accélération (MPU6050)
const int minAcc = -16384;  // Valeur minimale pour l'accélération (MPU6050)
const int maxGyro = 32767;  // Valeur maximale pour la rotation (MPU6050)
const int minGyro = -32767; // Valeur minimale pour la rotation (MPU6050)

void setup() {
  Serial.begin(9600);
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
  radio.setPowerLevel(20);
  Serial.println(F("Initialize System"));
  if (!mpu.begin(0x69)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, temp;
 	mpu.getEvent(&a, &g, &temp);
  struct Mpu6050 {
    int ax;
    int ay;
    int az;
    int rx;
    int ry;
    int rz;
  };
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
