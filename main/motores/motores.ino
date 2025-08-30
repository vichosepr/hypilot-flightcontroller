#include <ESP32Servo.h>

Servo esp_1, esp_2, esp_3, esp_4;

float basePower = 2000;

extern float accel_ang_x, accel_ang_y;

void setup() {
  esp_1.attach(,1000, 2000);
  esp_2.attach(,1000, 2000);
  esp_3.attach(, 1000, 2000);
  esp_4.attach(, 1000, 2000);

  //1000 apagados, 1500 media, 2000 maxima
}

void loop() {
  float err_x = 0 - accel_ang_x;
  float err_y = 0 - accel_ang_y;
}

void takeoff(int power){
  esp_1.writeMicroseconds(power);
  esp_2.writeMicroseconds(power);

  esp_3.writeMicroseconds(power);
  esp_4.writeMicroseconds(power);
}

void moveforward(int power){
  //abajar velocidad de motores
  esp_1.writeMicroseconds(power);
  esp_2.writeMicroseconds(power); 

  esp_3.writeMicroseconds(power);
  esp_4.writeMicroseconds(power);
}

void movebackward(int power){
  //abajar velocidad de motores
  esp_3.writeMicroseconds(power - 500);
  esp_4.writeMicroseconds(power - 500);

  esp_1.writeMicroseconds(power);
  esp_2.writeMicroseconds(power);
}

void moveRight(int power){
  esp_3.writeMicroseconds(power - 500);
  esp_1.writeMicroseconds(power - 500);

  esp_4.writeMicroseconds(power);
  esp_2.writeMicroseconds(power);
}

void moveLeft(int power){
  esp_4.writeMicroseconds(power - 500);
  esp_2.writeMicroseconds(power - 500);

  esp_3.writeMicroseconds(power);
  esp_1.writeMicroseconds(power);
}







