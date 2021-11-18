/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

#define spkPin 4
bool spkState = false;
MPU6050 mpu;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  pinMode(spkPin,OUTPUT);
}

void loop()
{
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  // Output
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);

  if(pitch>=50 || pitch<=-50){
    Serial.print("alert");
    delay(1000);
    spkState = true;
   
    while(spkState){
      Vector normAccel = mpu.readNormalizeAccel();
      int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
      int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
      tone(spkPin,3520);
      delay(200);
      noTone(spkPin);
      delay(100);
      if(pitch<50 && pitch>-50){
        for(int i=0;i<4;i++){
          tone(spkPin,3520);
          delay(200);
          noTone(spkPin);
          delay(100);
        }
        spkState=false;
      }
 
    }

  }else{
    spkState=false;  
  }

  if(roll>=50 || roll<=-50){
    Serial.print("alert");
    delay(1000);
    spkState = true;
   
    while(spkState){
      Vector normAccel = mpu.readNormalizeAccel();
      int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
      int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
      tone(spkPin,3520);
      delay(200);
      noTone(spkPin);
      delay(100);
      if(pitch<50 && pitch>-50){
        for(int i=0;i<4;i++){
          tone(spkPin,3520);
          delay(200);
          noTone(spkPin);
          delay(100);
        }
        spkState=false;
      }
 
    }

  }else{
    spkState=false;  
  }
  
  Serial.println();
  delay(2000);
}
