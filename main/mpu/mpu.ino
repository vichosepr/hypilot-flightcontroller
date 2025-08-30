#include <MPU6050.h>
#include <Wire.h>

MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t ax_offset, ay_offset, az_offset;
int16_t gx_offset, gy_offset, gz_offset;
int16_t corr_ax, corr_ay, corr_az;
int16_t corr_gx, corr_gy, corr_gz;

#define RAD_TO_DEG 57.2957795131

void setup()
{
  Serial.begin(115200);

  //sda y ssl
  Wire.begin(21, 22);
  mpu.initialize();
  getOffsets();
  
  if (mpu.testConnection()) {
    Serial.println("Sensor iniciado");
  }
  else {
    Serial.println("Error");
  }
}

void loop(){
  readAcceleration();
  readRotation();
  readAngles();

}


void getOffsets(){
  ax_offset = mpu.getXAccelOffset();
  ay_offset = mpu.getYAccelOffset();
  az_offset = mpu.getZAccelOffset();
  gx_offset = mpu.getXGyroOffset();
  gy_offset = mpu.getYGyroOffset();
  gz_offset = mpu.getZGyroOffset();
}



//leer datos con la mpu y calibrala
void readAcceleration(){
  mpu.getAcceleration(&ax, &ay, &az);
  corr_ax = ax - ax_offset;
  corr_ay = ay - ay_offset;
  corr_az = az - az_offset;
}

void readRotation(){
  mpu.getRotation(&gx, &gy, &gz);
  corr_gx = gx - gx_offset;
  corr_gy = gy - gy_offset;
  corr_gz = gz - gz_offset;
}

void readAngles(){
  float accel_ang_x= (atan(corr_ax/sqrt(pow(corr_ay,2) + pow(corr_az,2))))*RAD_TO_DEG; //roll
  float accel_ang_y= (atan(corr_ay/sqrt(pow(corr_ax,2) + pow(corr_az,2))))*RAD_TO_DEG; //pitch
  Serial.print(accel_ang_x);
  Serial.print(accel_ang_y);
}


