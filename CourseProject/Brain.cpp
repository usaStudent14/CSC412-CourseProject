#include "Brain.h"

/**
 * performs all related logic to read from sensors and store the value in a
 * usable form
 */
void Brain::think()
{
    int leftLight  = Brain::clamp(this->leftLight->readRaw(), Brain::MIN_LEFT_LIGHT, Brain::MAX_LEFT_LIGHT);
    int rightLight = Brain::clamp(this->rightLight->readRaw(), Brain::MIN_RIGHT_LIGHT, Brain::MAX_RIGHT_LIGHT);

    this->leftLightReal  = (double) (leftLight - Brain::MIN_LEFT_LIGHT) / (Brain::MAX_LEFT_LIGHT - Brain::MIN_LEFT_LIGHT);
    this->rightLightReal = (double) (rightLight - Brain::MIN_RIGHT_LIGHT) / (Brain::MAX_RIGHT_LIGHT - Brain::MIN_RIGHT_LIGHT);
    
    this->sonarReal = this->sonar->getDist();

    int leftDelta  = 0;
    int rightDelta = 0;

    if(this->leftLightReal > 0.0)
    {
      leftDelta = -1 * (pow(this->leftLightReal, 2) * Brain::MAX_TURN);
    }

    if(this->rightLightReal > 0.0)
    {
      rightDelta = 1 * (pow(this->rightLightReal, 2) * Brain::MAX_TURN);
    }

    this->turnDeltaReal = Brain::clamp(leftDelta + rightDelta, Brain::MIN_TURN, Brain::MAX_TURN);

    return;
}

int Brain::clamp(int value, int lower, int upper)
{
  if(value < lower)
    return lower;

  if(value > upper)
    return upper;

  return value;
}

