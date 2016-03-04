

#include <BMI160.h>
#include <CurieImu.h>

#include <MadgwickAHRS.h>

#include <Adafruit_MotorShield.h>


//Setup dor Madgwick, general vars
Madgwick filterMadgwick;
int axC, ayC, azC;
int gxC, gyC, gzC;
float yaw, pitch, roll;
int factor = 800; //Sensitivity of CurieIMU sensor

int CalibrateOffsets = 1; //Calibration yes/no?
int M1 = 3;
int M2 = 5;
int M3 = 6;
int M4 = 9;

int c = -1;  //factor for yaw, pitch, roll
void setup() {
  // comm. Setup
  Serial.begin(9600);

  //initialization
  CurieImu.initialize();

  //test connection
  if(!CurieImu.testConnection()){
    Serial.println("CurieImu couldn't connect");
  } else {
    Serial.println("CurieImu connected");
  }

  if(CalibrateOffsets == 1){
    
  //calibrate offset
    Serial.println("Internal sensor offsets BEFORE calibration...");
    Serial.print(CurieImu.getXAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getYAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getZAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getXGyroOffset()); Serial.print("\t");
    Serial.print(CurieImu.getYGyroOffset()); Serial.print("\t");
    Serial.print(CurieImu.getZGyroOffset()); Serial.print("\t");
    Serial.println("");
    //Calibrating IMU; keep IMU level and horizontal for this step
    
    Serial.print("Starting calibration... keep Device horizontal and level.");
    CurieImu.autoCalibrateGyroOffset();
    CurieImu.autoCalibrateXAccelOffset(0);
    CurieImu.autoCalibrateYAccelOffset(0);
    CurieImu.autoCalibrateZAccelOffset(1);
    Serial.println("Calibration finished");

    Serial.println("Internal sensor offsets AFTER calibration...");
    Serial.print(CurieImu.getXAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getYAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getZAccelOffset()); Serial.print("\t");
    Serial.print(CurieImu.getXGyroOffset()); Serial.print("\t");
    Serial.print(CurieImu.getYGyroOffset()); Serial.print("\t");
    Serial.print(CurieImu.getZGyroOffset()); Serial.print("\t");
    Serial.println("");

    //Enabling offset compensation
    Serial.println("Enabling Gyroscope/Acceleration offset compensation");
    CurieImu.setGyroOffsetEnabled(true);
    CurieImu.setAccelOffsetEnabled(true);
    
    
  }
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
}

void loop() {
  //read raw IMU-Data
  axC = CurieImu.getAccelerationX();
  ayC = CurieImu.getAccelerationY();
  azC = CurieImu.getAccelerationZ();
  gxC = CurieImu.getRotationX();
  gyC = CurieImu.getRotationY();
  gzC = CurieImu.getRotationZ();

  //using Madgwick-Algorythm to return quaterions
  filterMadgwick.updateIMU(gxC / factor, gyC / factor, gzC / factor, axC, ayC, azC);

  //find yaw, roll, pitch from quaternions
  yaw = filterMadgwick.getYaw();
  roll = filterMadgwick.getRoll();
  pitch = filterMadgwick.getPitch();

  if (Serial.available() > 0) {
    int val = Serial.read();
    if (val == 's') { // if incoming serial is "s"
      Serial.print(yaw & " , " & yaw*c;
      Serial.print(","); // print comma so values can be parsed
      Serial.print(pitch);
      Serial.print(","); // print comma so values can be parsed
      Serial.println(roll);
    }
  }
    analogWrite(M1, yaw*c);
    analogWrite(M2, pitch*c);
    analogWrite(M3, roll*c);
/*
  //Section for debugging only

  Serial.print(axC); Serial.print("\t");
  Serial.print(ayC); Serial.print("\t");
  Serial.print(azC); Serial.print("\t");
  Serial.print(gxC); Serial.print("\t");
  Serial.print(gyC); Serial.print("\t");
  Serial.print(gzC); Serial.print("\t");
  Serial.println("");
*/

}
