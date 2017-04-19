#ifndef PILOT_H
#define PILOT_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>
#include <NXTUS.h>
#include "Brain.h"
#include "Avoid.h"

class Pilot {

  private:
    NXShield* m_shield;
    Brain*    m_brain;
    Avoid*    m_avoid;

    int maxSpeed     = 100;
    int currentSpeed = 0;
    int steerAngle   = 0;
    
  public:
    void init();
    
    void setShield(NXShield* shield);
    void setBrain(Brain* brain);
    void setAvoid(Avoid* avoid);
    void resetMotors();
    
    void drive();
    void fullStop();
    void slowStop();
    void setSpeed(int speed);
    void turn(int heading, int turnSpeed);
    void centerSteer();
    void zeroSteer();
};

#endif

