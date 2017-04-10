#ifndef BRAIN_H
#define BRAIN_H

#include <Arduino.h>
#include <NXTLight.h>
#include <NXTUS.h>

class Brain
{
  public:
    static const int THRESHOLD = 475;
    
    NXTLight *m_leftLight;
    NXTLight *m_centerLight;
    NXTLight *m_rightLight;
    NXTUS    *m_sonar;
  
    bool leftFlag   = false;
    bool centerFlag = true;
    bool rightFlag  = false;
    
    int targetHeading = 0;
    
    void think();
    static int clamp(int lower, int value, int upper);
};

#endif
