#include <ESP32Servo.h>
#include <MPU6050.h>
#include <Wire.h>
//cada controlador
Servo esc_1, esc_2, esc_3, esc_4;

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t ax_offset, ay_offset, az_offset;
int16_t gx_offset, gy_offset, gz_offset;
int16_t corr_ax, corr_ay, corr_az;
int16_t corr_gx, corr_gy, corr_gz;

void setup()
{
  esc_1.attach(9);
  esc_2.attach(10);
  esc_3.attach(11);
  esc_4.attach(12);

  Serial.begin(9600);

  Wire.begin(21, 22);
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("Sensor iniciado");
  }
  else {
    Serial.println("Error");
  }
}

void loop()
{
  readAcceleration();
  readRotation();
  readAngles();
  calibrateOffsets()
}
void readAcceleration(){
  mpu.getAcceleration(&ax, &ay, &az);
}

void readRotation(){
  mpu.getRotation(&gx, &gy, &gz);
}

void readAngles(){
  float accel_ang_x= atan(ax/sqrt(pow(ay,2) + pow(az,2)));
  float accel_ang_y= atan(ay/sqrt(pow(ax,2) + pow(az,2)));

  Serial.print(accel_ang_x);
  Serial.print(accel_ang_y);
}

void calibrateOffsets(){
  mpu.getXAccelOffset(&ax_offset);
  mpu.getYAccelOffset(&ay_offset);
  mpu.getZAccelOffset(&az_offset);
  mpu.getXGyroOffset(&gx_offset);
  mpu.getYGyroOffset(&gy_offset);
  mpu.getZGyroOffset(&gz_offset);

  corr_ax = ax - ax_offset;
  corr_ay = ay - ay_offset;
  corr_az = az - az_offset;
  corr_gx = gx - gx_offset;
  corr_gy = gy - gy_offset;
  corr_gz = gz - gz_offset;

  mpu.setXAccelOffset(corr_ax);
  mpu.setYAccelOffset(corr_ay);
  mpu.setZAccelOffset(corr_az);
  mpu.setXGyroOffset(corr_gx);
  mpu.setYGyroOffset(corr_gy);
  mpu.setZGyroOffset(corr_gz);
}
