#include "Brain.h"

/**
 * gives the Brain a pointer to the left NXTLight
 */
void Brain::setLeftLight(NXTLight *lightLeft)
{
    this.m_lightLeft = lightLeft;
    return;
}

/**
 * gives the Brain a pointer to the right NXTLight
 */
void Brain::setRightLight(NXTLight *lightRight)
{
    this.m_lightRight = lightRight;
    return;
}

/**
 * gives the Brain a pointer to the NXTSonar
 */
void Brain::setSonar(NXTSonar *sonar)
{
    this.m_sonar = sonar;
    return;
}

/**
 * performs all related logic to read from sensors and store the value in a
 * usable form
 */
void Brain::think()
{
    int rawLeft  = this.m_lightLeft->readRaw();
    int rawRight = this.m_lightRight->readRaw();

    this.m_lightLeftValue  = (float) (rawLeft - Brain::MIN_LIGHT_LEFT) / (Brain::MAX_LIGHT_LEFT - Brain::MAX_LIGHT_RIGHT);
    this.m_lightRightValue = (float) (rawRight - Brain::MIN_LIGHT_RIGHT) / (Brain::MAX_LIGHT_RIGHT - Brain::MIN_LIGHT_RIGHT);

    return;
}

/**
 * returns a copy of the current light sensor information
 */
LightData Brain::getLightData()
{
    LightData ld = new LightData();

    ld.lightLeft  = this.m_lightLeftValue;
    ld.lightRight = this.m_lightRightValue;

    return ld;
}

/**
 * returns a copy of the current sonar sensor information
 */
SonarData Brain::getSonarData()
{
    SonarData sd = new SonarData();

    sd.sonar = this.m_sonarValue;

    return sd;
}
