// Auto Race Car v.1

#include <NXShield.h>
#include <Wire.h>
#include <NXTLight.h>
#include <NXTUS.h>
#include "Pilot.h"

NXShield nxshield;
NXTLight r_Light;
NXTLight l_Light;
NXTUS proxSensor;
Pilot motorPilot(nxshield);

void setup() {
  // Set serial baude rate
  Serial.begin(9600);

  // Initialize NXT components
  nxshield.init(SH_HardwareI2C);
  r_Light.init(&nxshield, SH_BBS2);
  l_Light.init(&nxshield, SH_BBS1);
  proxSensor.init(&nxshield, SH_BAS2);
  
  r_Light.setReflected();
  l_Light.setReflected();

  motorPilot.resetMotors();
  
  // Wait for button press to start control loop
  nxshield.waitForButtonPress(BTN_GO);
}

void loop() {
  // Start drive motors
  motorPilot.driveAtSpeed(50);
  
  // Poll proximity sensor
    // Slow or stop drive motor
    // Object avoidance routine
    
  // Poll light sensors
  float ep0 = pollSensor(0);// left sensor
  float ep1 = pollSensor(1); // right sensor

  // Check sensor readings
  motorPilot.driveAtSpeed(deriveDriveSpeed(ep0, ep1));
  
  // Turn right or left
  turn(ep0, ep1);

  // Press button RIGHT on NXShield to pause the robot
  // Press button GO to start again
  if(nxshield.getButtonState(BTN_RIGHT)){
    while(!nxshield.getButtonState(BTN_GO)){}
  }

}

// Returns percentege of engagement for given sensor - 
// 0 is left sensor, 1 is right sensor
float pollSensor(int sensor){
  // STUB
  return 0.0;
}

// Derives drive wheel speed from given sensor engagement
// percentages
int deriveDriveSpeed(float leftPercent, float rightPercent){
  // STUB
  return 0;
}

// Derives a target wheel orientation and turn speed from
// given sensor engagement percentages. Calls pilot turn
// function.
void turn(float leftPercent, float rightPercent){
  // STUB
  int targetAngle = 0;
  int turnSpeed = 0;
  
  motorPilot.turn(targetAngle, turnSpeed);
}

