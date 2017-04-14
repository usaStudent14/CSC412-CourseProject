// Auto Race Car v.1

#include <NXShield.h>
#include <Wire.h>
#include <NXTLight.h>
#include <NXTUS.h>
#include "Pilot.h"
#include "Brain.h"

NXShield shield;
NXTLight light_l;
NXTLight light_r;
NXTUS    sonar;
Brain    brain;
Pilot    pilot;
Avoid    avoid;

/**
 * NOTE: SH_BAS1 is a dead port!
 */

void setup()
{
  // Configure Serial
  Serial.begin(9600);
  Serial.println("setup()");
  
  // Initialize
  Serial.println("Initializing NXT components...");
  shield.init(SH_HardwareI2C);
  light_l.init(&shield, SH_BAS2);
  light_r.init(&shield, SH_BBS2);
  sonar.init(&shield, SH_BBS1);

  Serial.println("Linking sensors to brain...");
  brain.setLights(&light_l, &light_r);
  brain.setSonar(&sonar);

  Serial.println("Linking brain to avoid...");
  avoid.setBrain(&brain);

  Serial.println("Linking shield, brain, and avoid to pilot...");
  pilot.setShield(&shield);
  pilot.setBrain(&brain);
  pilot.setAvoid(&avoid);

  Serial.println("Initializing brain, avoid, and pilot...");
  brain.init();
  avoid.init();
  pilot.init();
  
  // Wait for button press to start control loop
  Serial.println("Waiting for go...");
  shield.waitForButtonPress(BTN_GO);
}

void loop()
{
  Serial.println("loop()");
  pilot.drive(100);
}
