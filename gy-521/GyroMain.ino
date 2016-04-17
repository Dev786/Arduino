#include<MPU6050.h>
#include<Wire.h>
#include<I2Cdev.h>
#define toDegree 180/PI
int16_t ax;
int16_t ay;
int16_t az;
int16_t gx;
int16_t gy;
int16_t gz;

int accelOffset = 200;
int accelReading = 0;
MPU6050 accelgyro;
float lastGyroX = 0;
float lastGyroY = 0;
float lastGyroZ = 0;
unsigned long lastTime;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  
  accelgyro.initialize();
  accelgyro.setXGyroOffset(40);
  accelgyro.setYGyroOffset(40);
  accelgyro.setZGyroOffset(60);
  
  lastTime = millis();
}


void loop()
{

  unsigned long newTime = millis();
  unsigned long dt = (newTime - lastTime)/1000;
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  
  float angX = atan((ax) / (sqrt(pow(ay, 2) + pow(az, 2)))) *toDegree;
  float angY = atan((ay) / (sqrt(pow(ax, 2) + pow(az, 2)))) *toDegree;
  

 float angGX = lastGyroX + ((gx-accelgyro.getXGyroOffset()) / 131)*dt;
 float angGY = lastGyroY + ((gy-accelgyro.getYGyroOffset()) / 131)*dt;
  
  float alpha = 0.96;
  float usefulX = alpha * angGX - (1-alpha)*angX;
  float usefulY = alpha * angGY - (1-alpha)*angY;
  
  lastGyroX = usefulX;
  lastGyroY = usefulY;
  
/*  Serial.print("AccelXYZ:  ");
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.print(az);
  Serial.print("\n");

  Serial.print("GyroXYZ:  ");
  Serial.print(gx);
  Serial.print(", ");
  Serial.print(gy);
  Serial.print(", ");
  Serial.print(gz);
  Serial.print("\n");

  Serial.print("AccelAngXY:  ");
  Serial.print(angX);
  Serial.print(", ");
  Serial.print(angY);
  Serial.print("\n");

  Serial.print("MainAngXY:  ");
  Serial.print(usefulX);
  Serial.print(", ");
  Serial.print(usefulY);
  Serial.print("\n");
*/
  Serial.print(usefulX);
  Serial.print(",");
  Serial.print(usefulY);
  Serial.print("\n");

  lastTime = millis();
  
  }
