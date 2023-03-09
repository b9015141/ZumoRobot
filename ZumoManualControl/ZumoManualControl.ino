  #include <Wire.h>
  #include <Zumo32U4.h>

 // Robot Components
  Zumo32U4Motors motors;
  Zumo32U4ButtonA buttonA; 
  Zumo32U4Buzzer buzzer;
  Zumo32U4LineSensors lineSensors;
  Zumo32U4ProximitySensors proxSensors;
  Zumo32U4IMU imu;
  
  //variable to read incoming serial data into
  int incomingByte;  

  //array light sensors
  uint16_t lineSensorValues[3] = {0, 0, 0};

  const uint16_t motorSpeed = 200;
  const uint16_t turnSpeed = 150;
 

  #define FORWARD_SPEED 150
  #define EDGE_THRESHOLD 150
  #define EDGE_TOLERANCE 50    //The tolerance is a way to calculate how close to square is the robot.
  #define KPsq 0.6

 
 // Global Variables

  bool proxLeftActive;
  bool proxFrontActive;
  bool proxRightActive;
  bool turnAngle;

  int curSpeed = 0;
  int acceleration = 1;
 
  char action;
  int speed = 100;

  const int turnSensorReset();
  const int turnSensorUpdate();


  void setup() {
  
   // initialize serial communication:
    Serial1.begin(9600);
  
    //initialize Sensors
    lineSensors.initThreeSensors();
    calLightSensors(10); 
    proxSensors.initThreeSensors(); 
  }

 // Functions 
 
 //turn left 
 void turnLeft(int degrees) {
   turnSensorReset();
   motors.setSpeeds(-turnSpeed, turnSpeed);
   int angle = 0;
   do {
     delay(1);
     turnSensorUpdate();
     angle = (((int32_t)turnAngle >> 16) *360) >> 16;
   } while (angle < degrees);
   motors.setSpeeds(0, 0);
 }

 //Turn right 
 void turnRight(int degrees) {
   turnSensorReset();
   motors.setSpeeds(turnSpeed, -turnSpeed);
   int angle = 0;
   do {
     delay(1);
     turnSensorUpdate();
     angle = (((int32_t)turnAngle >> 16) *360) >> 16;
   } while (angle < -degrees);
   motors.setSpeeds(0, 0);
 }

 //Stop 
 void stop() {
   motors.setSpeeds(0, 0);
 }

 //Go forward
  void forward() {

    int angle = 0;
    turnSensorUpdate();
    angle = (((int32_t)turnAngle >> 16) * 360) >> 16;

    //move forward, adjusting motor speed to hold heading
    motors.setSpeeds(curSpeed + (angle * 5), curSpeed - (angle * 5));

  }

 //Reverse
  void reverse() {

   motors.setSpeeds(-motorSpeed, -motorSpeed);

  }

 //Look left
  void scanLeft() {

   motors.setSpeeds(-curSpeed, -curSpeed);

  }

 //Look right
  void scanRight() {

    motors.setSpeeds(curSpeed, -curSpeed);

  }

 //Change direction to the left
  void forwardLeft() {

   motors.setSpeeds(curSpeed / 2, curSpeed);

  }

 //Change direction to the right
  void forwardRight() {

   motors.setSpeeds(curSpeed, curSpeed / 2);
   
  }
 

  // Calibrating LineSensors

  void calLightSensors(int CalTime) { 

    buttonA.waitForButton(); 
    buzzer.playFrequency(440, 200, 15); 
    
      for (uint16_t i = 0; i < 400; i++) { 
        Serial1.print(i); 
        lineSensors.calibrate();
      } 
    
    buzzer.playFrequency(440, 50, 15); 
    Serial1.print("Cal Done"); 
    delay(1000);
  }
  

  // Setting motorSpeed once sensors are calibrated
  
  void drive2line(int motorSpeed) {

    Serial1.println("Press button A..");
    Serial1.println("Moving forward...");
    motors.setSpeeds(motorSpeed,motorSpeed);

    do {

      lineSensors.readCalibrated(lineSensorValues);

    } while (lineSensorValues[0]>EDGE_THRESHOLD && lineSensorValues[2]>EDGE_THRESHOLD);
    
    motors.setSpeeds(0,0);
    Serial1.println("Stopping...");
  } 


  //1. the value of the left and right light sensors.
  //2. Calculate the error of the left and right light sensors.
  //3. Calculate the correction factor of the left and right (correction is error times gain).
  //4. Apply the correction factor to the motor power.
  //5. Repeat as long as the left and right errors are larger than a certain tolerance.
  void square2line(int tol) {

   int errorLeft, errorRight, corrLeft, corrRight;

    do {

      lineSensors.readCalibrated(lineSensorValues);

      errorLeft=lineSensorValues[0]-500;
      errorRight=lineSensorValues[2]-500;

      corrLeft=-errorLeft*KPsq;
      corrRight=-errorRight*KPsq;

      motors.setLeftSpeed(corrLeft);
      motors.setRightSpeed(corrRight);

    } while (abs(errorLeft)>tol||abs(errorRight)>tol);

    motors.setSpeeds(0,0);

  }   


  void loop() 
  {

    Serial1.println("Press A"); 
    motors.setSpeeds(0, 0);
    buttonA.waitForButton();  
    buzzer.playFrequency(440, 200, 15); 
    delay(200);

   if (Serial1.available() > 0) 
    { 
      action = Serial1.read();  

      switch (action)
      {
        case 'w':
          // go forwards
          motors.setSpeeds (speed, speed);
          delay(100);
          break; 
        case 's':
          // go backwards
          motors.setSpeeds(speed*-1, speed*-1);
          delay(100);
          break;  
        case 'a':
          // turn left
          motors.setLeftSpeed(0);
          motors.setRightSpeed(speed);
          delay(100);
          break;   
        case 'd':
          // turn right
          motors.setLeftSpeed(speed);
          motors.setRightSpeed(0);
          delay(100);
          break;      
        default:
          motors.setLeftSpeed(0);
          motors.setRightSpeed(0);
          delay(100);
      }

      delay(500);
    }


    drive2line(FORWARD_SPEED);
    square2line(EDGE_TOLERANCE);

   //Proximity sensors
  
    proxSensors.read();  // Send IR pulses and read the proximity sensors.

    int left_sensor = proxSensors.countsLeftWithLeftLeds();
    int centerLeftSensor = proxSensors.countsFrontWithLeftLeds();
    int centerRightSensor = proxSensors.countsFrontWithRightLeds();
    int right_sensor = proxSensors.countsRightWithRightLeds();
   
    lineSensors.readCalibrated(lineSensorValues);  //Reading LINE SENSORS
  } 

  
  



