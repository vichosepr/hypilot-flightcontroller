#include <Servo.h>
#include <MPU6050.h>
//cada controlador 
Servo esc_1;
Servo esc_2;
Servo esc_3;
Servo esc_4;

//mpu
MPU6050 mpu;

int ax, ay, az;
int gx, gy, gz;

void setup()
{
  esc_1.attach(9);
  esc_2.attach(10);
  esc_3.attach(11);
  esc_4.attach(12);

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("Sensor iniciado correctamente");
  }
  else {
    Serial.println("Error al iniciar el sensor");
  }
}

void readAcceleration(){

}
