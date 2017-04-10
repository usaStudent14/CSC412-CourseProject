#include "Brain.h"

/**
 * performs all related logic to read from sensors and store the value in a
 * usable form
 */
void Brain::think()
{
  int leftLight   = this->m_leftLight->readRaw();
  int centerLight = this->m_centerLight->readRaw();
  int rightLight  = this->m_rightLight->readRaw();

  if(centerLight > Brain::THRESHOLD)
  {
    this->leftFlag   = false;
    this->centerFlag = true;
    this->rightFlag  = false;
  }

  if(leftLight > Brain::THRESHOLD)
  {
    this->leftFlag   = true;
    this->centerFlag = false;
    this->rightFlag  = false;
  }

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

  if(this->rightFlag)
  {
    this->targetHeading = 60;
  }
}

int Brain::clamp(int lower, int value, int upper)
{
  if(value < lower)
    return lower;

  if(value > upper)
    return upper;

  return value;
}

