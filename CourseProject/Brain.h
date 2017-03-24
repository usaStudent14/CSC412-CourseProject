#ifndef BRAIN_H
#define BRAIN_H

#include <Arduino.h>
#include <NXTLight.h>
#include <NXTUS.h>

class Brain
{
    public:
        static const int MIN_LEFT_LIGHT  = 350;
        static const int MAX_LEFT_LIGHT  = 530;
        static const int MIN_RIGHT_LIGHT = 400;
        static const int MAX_RIGHT_LIGHT = 560;
        static const int MIN_TURN_DELTA  = -60;
        static const int MAX_TURN_DELTA  = 60;
        
        NXTLight *leftLight;
        NXTLight *rightLight;
        NXTUS    *sonar;

        int   sonarReal      = 0;
        int   turnDeltaReal  = 0;
        float leftLightReal  = 0.0;
        float rightLightReal = 0.0;

        void think();
        int clamp(int lower, int value, int upper);
};

#endif
