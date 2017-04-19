#include "Avoid.h"
#include "Pilot.h"
#include "Brain.h"

/*
 * This file will interact with the brain and the pilot to gather sensor data and detect if an object is in the path.
 * If object is in the path then this will take over pilot control for a given period of time until object is passed.
 */

/**
 * initialize
 */
void Avoid::init()
{
  // TODO run init stuff here if needed

  return;
}

/**
 * set the brain pointer
 */
void Avoid::setBrain(Brain* brain)
{
  this->m_brain = brain;

  return;
}

void Avoid::checkLightBooleans()
{
  // TODO stub

  return;
}

void Avoid::checkObjectDistance()
{
  // TODO stub

  return;
}

void Avoid::checkSonarBoolean()
{
  // TODO stub

  return;
}

