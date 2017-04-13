#ifndef PILOT_H
#define PILOT_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>
#include "Brain.h"

class Pilot {

  private:
    NXShield * pnxshield;
    NXTLight * pNxLight_1;
    NXTLight * pNxLight_2;
    int maxSpeed;
    int currentSpeed;
    int steerAngle;
    Brain brain;
    
  public:
    Pilot(NXShield& nxt, NXTLight& r_l, NXTLight& l_l, NXTUS& sonar);
    Pilot(NXShield& nxt, NXTLight& r_l, NXTLight& l_l, NXTUS& sonar, int ms);
    void drive(int initialSpeed);
    void fullStop();
    void slowStop();
    void setSpeed(int speed);
    void turn(int heading, int turnSpeed);
    void centerSteer();
    void zeroSteer();
    void setMaxSpeed(int ms);
    int getMaxSpeed();
    void resetMotors();
};

#endif

