#include "Brain.h"

/**
 * clamp the incoming float between a lower and upper bounds inclusively
 */
float Brain::clamp(float lower, float value, float upper)
{
  if(value < lower)
    return lower;

  if(value > upper)
    return upper;

  return value;
}

/**
 * initialize the brain
 */
void Brain::init()
{
  Serial.println("Brain::init()");
  
  this->m_light_l->setReflected();
  this->m_light_r->setReflected();
  
  return;
}

/**
 * sets the light pointers
 */
void Brain::setLights(NXTLight* light_l, NXTLight* light_r)
{
  Serial.println("Brain::setLights()");
  
  this->m_light_l = light_l;
  this->m_light_r = light_r;

  // Calibrate light sensors
  int sensor_delta_sum = 0;
  for(int t = 0; t < 50; t++){
    int l_read = this->m_light_l->readRaw();
    int r_read = this->m_light_r->readRaw();
    int delta = l_read - r_read;
    sensor_delta_sum += delta;
  }

  // Set average delta
  this->light_sensor_delta = sensor_delta_sum/50;
  return;
}

/**
 * sets the sonar pointer
 */
void Brain::setSonar(NXTUS* sonar)
{
  Serial.println("Brain::setSonar()");
  
  this->m_sonar = sonar;
  
  return;
}

/**
 * returns calibrated delta between sensor readings
 */
int Brain::getSensorDelta(){
  return this->light_sensor_delta;
}


/**
 * processes the light sensors for structured data
 */
LightData Brain::getLightData()
{
  LightData ld;

  ld.raw_l = this->m_light_l->readRaw();
  ld.raw_r = this->m_light_r->readRaw();

  float percent_l = (ld.raw_l - Brain::LIGHT_L_MIN) / (Brain::LIGHT_L_MAX - Brain::LIGHT_L_MIN);
  float percent_r = (ld.raw_r - Brain::LIGHT_R_MIN) / (Brain::LIGHT_R_MAX - Brain::LIGHT_R_MIN);
  
  ld.percent_l = Brain::clamp(0.0, percent_l, 1.0);
  ld.percent_r = Brain::clamp(0.0, percent_r, 1.0);

  return ld;
}

/**
 * processes the sonar sensor for structured data
 */
SonarData Brain::getSonarData()
{
  SonarData sd;

  sd.raw = this->m_sonar->getDist();

  float percent = (sd.raw - Brain::SONAR_MIN) / (Brain::SONAR_MAX - Brain::SONAR_MIN);

  sd.percent = Brain::clamp(0.0, percent, 1.0);

  return sd;
}
