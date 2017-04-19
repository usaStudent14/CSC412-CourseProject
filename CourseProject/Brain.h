#ifndef BRAIN_H
#define BRAIN_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>
#include <NXTUS.h>

struct LightData
{
  int   raw_l = 0;
  int   raw_r = 0;
  float percent_l = 0.0;
  float percent_r = 0.0;
};

struct SonarData
{
  int   raw     = 0;
  float percent = 0.0;
};

class Brain
{
  private:
    NXTLight* m_light_l;
    NXTLight* m_light_r;
    NXTUS*    m_sonar;

    int light_sensor_delta = 0;

  public:
    static const int LIGHT_L_MIN = 0;   // TODO calibrate
    static const int LIGHT_L_MAX = 100; // TODO calibrate

    static const int LIGHT_R_MIN = 0;   // TODO calibrate
    static const int LIGHT_R_MAX = 100; // TODO calibrate
    
    static const int SONAR_MIN = 0;     // TODO calibrate
    static const int SONAR_MAX = 100;   // TODO calibrate
    
    static float clamp(float lower, float value, float upper);

    void init();
  
    void setLights(NXTLight* light_l, NXTLight* light_r);
    void setSonar(NXTUS* sonar);

    int getSensorDelta();
    
    LightData getLightData();
    SonarData getSonarData();
};

#endif
