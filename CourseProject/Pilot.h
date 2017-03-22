#ifndef PILOT_H
#define PILOT_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>

class Pilot {

  private:
    NXShield * pnxshield;
    int maxSpeed;
    int currentSpeed;
    int steerAngle;
    
  public:
    Pilot(NXShield& nxt);
    Pilot(NXShield& nxt, int ms);
    void fullStop();
    void slowStop();
    void driveAtSpeed(int speed);
    void turn(int turnDelta, int turnSpeed);
    void centerSteer();
    void setMaxSpeed(int ms);
    int getMaxSpeed();
    void resetMotors();
};

#endif

