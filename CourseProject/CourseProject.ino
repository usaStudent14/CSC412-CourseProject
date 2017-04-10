// Auto Race Car v.1

#include <NXShield.h>
#include <Wire.h>
#include <NXTLight.h>
#include <NXTUS.h>
#include "Pilot.h"

NXShield nxshield;
NXTLight r_Light;
NXTLight l_Light;
NXTLight m_light;
NXTUS proxSensor;
Pilot motorPilot(nxshield, r_Light, l_Light, proxSensor);

void setup() {
  // Set serial baude rate
  Serial.begin(9600);

  // Initialize NXT components
  nxshield.init(SH_HardwareI2C);
  r_Light.init(&nxshield, SH_BBS2);
  l_Light.init(&nxshield, SH_BBS1);
  m_light.init(&nxshield, SH_BAS2);
  proxSensor.init(&nxshield, SH_BAS1);
  
  r_Light.setReflected();
  l_Light.setReflected();
  m_light.setReflected();

  motorPilot.resetMotors();
  
  // Wait for button press to start control loop
  nxshield.waitForButtonPress(BTN_GO);

}

void loop() {
  // Start drive motors
 motorPilot.drive(20);
}

