#include <ESP32Servo.h>

Servo esp_1, esp_2, esp_3, esp_4;

#define MOTOR_1 13
#define MOTOR_2 14
#define MOTOR_3 15
#define MOTOR_4 16

int takeoffPower = 0;

void setup() {
  esp_1.attach(MOTOR_1,1000, 2000);
  esp_2.attach(MOTOR_2,1000, 2000);
  esp_3.attach(MOTOR_3, 1000, 2000);
  esp_4.attach(MOTOR_4, 1000, 2000);

  //1000 apagados, 1500 media, 2000 maxima
}

void loop() {
  
}

void takeoff(int maxPower, int variation){
  maxPower = constrain(maxPower, 1000, 2000);
  variation = constrain(variation, 0, 20);
  //despegue progesivo
  for(int i = 1000; i< maxPower; i+= variation){
    esp_1.writeMicroseconds(i);
    esp_2.writeMicroseconds(i);

    esp_3.writeMicroseconds(i);
    esp_4.writeMicroseconds(i);

    takeoffPower = i;

    delay(50);//milisegundos
  }
}

//motores traseros aumentan su potencia, delanteros disminuyen
void moveforward(int currentPower, int variation){

  for(int i = 0; i <= 100; i+= variation){
    int back = currentPower + i;
    int front = currentPower - i;

    esp_1.writeMicroseconds(front);
    esp_2.writeMicroseconds(front);

    esp_3.writeMicroseconds(back);
    esp_4.writeMicroseconds(back);

    delay(50);//milisegundos
  }
}

void movebackward(int currentPower, int variation){

  for(int i = 0; i <= 100; i+= variation){
    int back = currentPower - i;
    int front = currentPower + i;

    esp_1.writeMicroseconds(front);
    esp_2.writeMicroseconds(front);

    esp_3.writeMicroseconds(back);
    esp_4.writeMicroseconds(back);

    delay(50);//milisegundos
  }
}

void moveleft(int currentPower, int variation){

  for(int i = 0; i <= 100; i+= variation){
    int back = currentPower + i;
    int front = currentPower - i;

    esp_1.writeMicroseconds(front);
    esp_2.writeMicroseconds(front);

    esp_3.writeMicroseconds(back);
    esp_4.writeMicroseconds(back);

    delay(50);//milisegundos
  }
}
