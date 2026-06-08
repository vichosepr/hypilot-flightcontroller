#include <ESP32Servo.h>

Servo esp_1, esp_2, esp_3, esp_4;

#define MOTOR_1 13;
#define MOTOR_2 14;
#define MOTOR_3 15;
#define MOTOR_4 16;

int minPower = 1000;
int maxPower = 2000;

extern float accel_ang_x, accel_ang_y;

void setup() {
  esp_1.attach(MOTOR_1,1000, 2000);
  esp_2.attach(MOTOR_2,1000, 2000);
  esp_3.attach(MOTOR_3, 1000, 2000);
  esp_4.attach(MOTOR_4, 1000, 2000);

  //1000 apagados, 1500 media, 2000 maxima
}

void loop() {
  float err_x = 0 - accel_ang_x;
  float err_y = 0 - accel_ang_y;
}

//iniciar con potencia minima 
void takeoff(int power){
  power = constrain(power, 1000, 2000);
  //despegue progesivo
  for(int i = 1000; i< 2000; i+= 10){
    esp_1.writeMicroseconds(i);
    esp_2.writeMicroseconds(i);

    esp_3.writeMicroseconds(i);
    esp_4.writeMicroseconds(i);
  }
  
}

void moveforward(int power){
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
