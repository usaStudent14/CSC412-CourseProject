#ifndef BRAIN_H
#define BRAIN_H

#include <Arduino.h>
#include <Math.h>
#include <NXTLight.h>
#include <NXTUS.h>

class Brain
{
    public:
        static const int MIN_LEFT_LIGHT  = 350;
        static const int MAX_LEFT_LIGHT  = 530;
        static const int MIN_RIGHT_LIGHT = 415;
        static const int MAX_RIGHT_LIGHT = 570;
        static const int MIN_TURN        = -60;
        static const int MAX_TURN        = 60;
        
        NXTLight *leftLight;
        NXTLight *rightLight;
        NXTUS    *sonar;

        int    sonarReal      = 0;
        int    turnDeltaReal  = 0;
        double leftLightReal  = 0.0;
        double rightLightReal = 0.0;

        void think();
        int clamp(int value, int lower, int upper);
};

#endif
