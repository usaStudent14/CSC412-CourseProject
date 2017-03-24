#ifndef BRAIN_H
#define BRAIN_H

#include <Arduino.h>
#include <NXShield.h>
#include <NXTLight.h>

struct LightData
{
    float lightLeft;
    float lightRight;
};

struct SonarData
{
    int sonar;
}

class Brain
{
    private:
        NXTLight *m_lightLeft;
        NXTLight *m_lightRight;
        NXTSonar *m_sonar;

        float m_lightLeftValue;
        float m_lightRightValue;
        int m_sonarValue;

    public:
        static const int MIN_LIGHT_LEFT = 350;
        static const int MAX_LIGHT_LEFT = 530;
        static const int MIN_LIGHT_RIGHT = 400;
        static const int MAX_LIGHT_RIGHT = 560;

        void setLeftLight(NXTLight *lightLeft);
        void setRightLight(NXTLight *lightRight);
        void setSonar(NXTSonar *sonar);
        void think();

        SensorData getLightData();
};

#endif
