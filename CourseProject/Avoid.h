#ifndef AVOID_H
#define AVOID_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>
#include "Brain.h"

class Avoid
{
  private:
    Brain* m_brain;
  public:
    void init();
  
    void setBrain(Brain* brain);
    
    void checkLightBooleans();
    void checkObjectDistance();
    void checkSonarBoolean();
};

#endif
