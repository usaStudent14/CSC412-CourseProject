#ifndef AVOID_H
#define AVOID_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>

class Avoid {
  private:
    boolean leftSensor = false;
    boolean rightSensor = false;
    boolean sonarSensor = false;
    void getDistance();
    void getLights();
  public:
    void checkLightBooleans();
    void checkObjectDistance();
    void checkSonarBoolean();
};

#endif
