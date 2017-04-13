#include "Brain.h"

/**
 * performs all related logic to read from sensors and store the value in a
 * usable form
 */
void Brain::think()
{
<<<<<<< HEAD
    int leftLight  = Brain::clamp(this->leftLight->readRaw(), Brain::MIN_LEFT_LIGHT, Brain::MAX_LEFT_LIGHT);
    int rightLight = Brain::clamp(this->rightLight->readRaw(), Brain::MIN_RIGHT_LIGHT, Brain::MAX_RIGHT_LIGHT);

    this->leftLightReal  = (double) (leftLight - Brain::MIN_LEFT_LIGHT) / (Brain::MAX_LEFT_LIGHT - Brain::MIN_LEFT_LIGHT);
    this->rightLightReal = (double) (rightLight - Brain::MIN_RIGHT_LIGHT) / (Brain::MAX_RIGHT_LIGHT - Brain::MIN_RIGHT_LIGHT);
    
    this->sonarReal = this->sonar->getDist();
=======
  int leftLight   = this->m_leftLight->readRaw();
  int centerLight = this->m_centerLight->readRaw();
  int rightLight  = this->m_rightLight->readRaw();

  if(centerLight > Brain::THRESHOLD)
  {
    this->leftFlag   = false;
    this->centerFlag = true;
    this->rightFlag  = false;
  }
>>>>>>> origin/master

  if(leftLight > Brain::THRESHOLD)
  {
    this->leftFlag   = true;
    this->centerFlag = false;
    this->rightFlag  = false;
  }

<<<<<<< HEAD
    if(this->leftLightReal > 0.0)
    {
      leftDelta = -1 * (pow(this->leftLightReal, 2) * Brain::MAX_TURN);
    }

    if(this->rightLightReal > 0.0)
    {
      rightDelta = 1 * (pow(this->rightLightReal, 2) * Brain::MAX_TURN);
    }

    this->turnDeltaReal = Brain::clamp(leftDelta + rightDelta, Brain::MIN_TURN, Brain::MAX_TURN);
=======
  if(rightLight > Brain::THRESHOLD)
  {
    this->leftFlag   = false;
    this->centerFlag = false;
    this->rightFlag  = true;
  }

  Serial.print("L: "); Serial.println(this->leftFlag);
  Serial.print("C: "); Serial.println(this->centerFlag);
  Serial.print("R: "); Serial.println(this->rightFlag);

  if(this->leftFlag)
  {
    this->targetHeading = -60;
  }

  if(this->centerFlag)
  {
    this->targetHeading = 0;
  }
>>>>>>> origin/master

  if(this->rightFlag)
  {
    this->targetHeading = 60;
  }
}

<<<<<<< HEAD
int Brain::clamp(int value, int lower, int upper)
=======
int Brain::clamp(int lower, int value, int upper)
>>>>>>> origin/master
{
  if(value < lower)
    return lower;

  if(value > upper)
    return upper;

  return value;
}

