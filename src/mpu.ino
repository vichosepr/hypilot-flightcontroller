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
  Serial.begin(9600);
  delay(1000);

  // SDA y SCL para NodeMCU (ESP8266)
  Wire.begin(4, 5);
  mpu.initialize();
  getOffsets();

  if (mpu.testConnection()) {
    Serial.println("Sensor iniciado");
  }
  else {
    Serial.println("Error");
  }
}

void loop() {
  readAcceleration();
  readRotation();
  delay(1000);
  readAngles();
}

void getOffsets() {
  ax_offset = mpu.getXAccelOffset();
  ay_offset = mpu.getYAccelOffset();
  az_offset = mpu.getZAccelOffset();
  gx_offset = mpu.getXGyroOffset();
  gy_offset = mpu.getYGyroOffset();
  gz_offset = mpu.getZGyroOffset();
}

// Leer datos del acelerómetro y compensar offset
void readAcceleration() {
  mpu.getAcceleration(&ax, &ay, &az);
  corr_ax = ax - ax_offset;
  corr_ay = ay - ay_offset;
  corr_az = az - az_offset;
  Serial.println("Lectura de aceleración:");
  Serial.println("AX: " + String(ax));
  Serial.println("AY: " + String(ay));
  Serial.println("AZ: " + String(az));
}

// Leer datos del giroscopio y compensar offset
void readRotation() {
  mpu.getRotation(&gx, &gy, &gz);
  corr_gx = gx - gx_offset;
  corr_gy = gy - gy_offset;
  corr_gz = gz - gz_offset;
  Serial.println("Lectura de rotación:");
  Serial.println("GX: " + String(gx));
  Serial.println("GY: " + String(gy));
  Serial.println("GZ: " + String(gz));
}

// Calcular ángulos a partir del acelerómetro
void readAngles() {
  float accel_ang_x = (atan(corr_ax / sqrt(pow(corr_ay, 2) + pow(corr_az, 2)))) * RAD_TO_DEG; // roll
  float accel_ang_y = (atan(corr_ay / sqrt(pow(corr_ax, 2) + pow(corr_az, 2)))) * RAD_TO_DEG; // pitch
  Serial.println("Ángulos:");
  Serial.println("Acelerómetro (X / Roll): " + String(accel_ang_x));
  Serial.println("Acelerómetro (Y / Pitch): " + String(accel_ang_y));
}
