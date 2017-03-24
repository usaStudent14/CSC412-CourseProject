#include "Brain.h"

/**
 * performs all related logic to read from sensors and store the value in a
 * usable form
 */
void Brain::think()
{
    int leftLight  = this.leftLight->readRaw();
    int rightLight = this.rightLight->readRaw();

    this.leftLightReal  = (float) (leftLight - Brain::MIN_LEFT_LIGHT) / (Brain::MAX_LEFT_LIGHT - Brain::MIN_LEFT_LIGHT);
    this.rightLightReal = (float) (rightLight - Brain::MIN_RIGHT_LIGHT) / (Brain::MAX_RIGHT_LIGHT - Brain::MIN_RIGHT_LIGHT);

    this.sonarReal = this.sonar->readRaw();

    int leftDelta  = 0;
    int rightDelta = 0;

    if(this.leftLightReal > 0.0)
    {
      leftDelta = -1 * (this.leftLightReal * Brain::MAX_TURN_DELTA);
    }

    if(this.rightLightReal > 0.0)
    {
      rightDelta = 1 * (this.rightLightReal * Brain::MAX_TURN_DELTA);
    }

    int turnDeltaReal = Brain::clamp(Brain::MIN_TURN_DELTA, leftDelta + rightDelta, Brain::MAX_TURN_DELTA);

    return;
}

/**
 * clamps a value between and upper and lower bound inclusivly
 */
int Brain::clamp(int lower, int value, int upper)
{
  if(value > upper)
  {
    return upper
  }
  
  if(value < lower)
  {
    return lower;
  }
  
  return value;
}


