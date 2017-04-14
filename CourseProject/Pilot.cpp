#include "Pilot.h"

/**
 * initialize the pilot
 */
void Pilot::init()
{
  Serial.println("Pilot::init()");
  
  this->resetMotors();

  return;
}

/**
 * sets the shield pointer
 */
void Pilot::setShield(NXShield* shield)
{
  Serial.println("Pilot::setShield()");
  
  this->m_shield = shield;

  return;
}

/**
 * sets the brain pointer
 */
void Pilot::setBrain(Brain* brain)
{
  Serial.println("Pilot::setBrain()");
  
  this->m_brain = brain;

  return;
}

/**
 * sets the avoid pointer
 */
void Pilot::setAvoid(Avoid* avoid)
{
  Serial.println("Pilot::setAvoid()");

  this->m_avoid = avoid;

  return;
}

/**
 * resets both motor banks
 */
void Pilot::resetMotors()
{
  this->m_shield->bank_a.motorReset();
  this->m_shield->bank_b.motorReset();

  return;
}

// Full driving functionality
void Pilot::drive(int initialSpeed)
{
  this->setSpeed(initialSpeed);
  
  LightData ld = this->m_brain->getLightData();

  int weight  = 100 / initialSpeed;
  int error   = ld.raw_l - (ld.raw_r - 50);
  int speed_l = initialSpeed - (error / weight);
  int speed_r = initialSpeed + (error / weight);
  
  this->m_shield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, speed_l);
  this->m_shield->bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, speed_r);

  return;
}

void Pilot::fullStop()
{
  this->m_shield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
  this->m_shield->bank_b.motorStop(SH_Motor_1, SH_Next_Action_Brake);

  return;
}

void Pilot::slowStop()
{
  while(this->currentSpeed >= 1)
  {
    this->currentSpeed = this->currentSpeed - (this->currentSpeed / 8);
    
    this->m_shield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, this->currentSpeed);
    this->m_shield->bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, this->currentSpeed);
    
    delay(50);
  }
  
  this->m_shield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);

  return;
}

void Pilot::setSpeed(int s)
{
  if(s > this->maxSpeed || s == -1)
  {
    this->currentSpeed = this->maxSpeed;
  }
  else
  {
    this->currentSpeed = s;
  }
  
  this->m_shield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, this->currentSpeed);
  this->m_shield->bank_b.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, this->currentSpeed);

  return;
}

// Recieves a degree amount to turn; left degrees are negative, right are positive;
// Degree 0 is at center steer
/*
void Pilot::turn(int heading, int turnSpeed)
{
  if(heading < steerAngle)
  {
    this->m_shield->bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, this->turnSpeed, 
<<<<<<< HEAD
                                      1, 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
   steerAngle = steerAngle - 1;
  }else if(heading > steerAngle){// Right turn
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Forward, 
                                      turnSpeed, 
                                      1, 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
    steerAngle = steerAngle + 1;
=======
                                      2, 
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_Brake);
   steerAngle = Brain::clamp(-60, steerAngle - 2, 60);
  }else if((heading > steerAngle)) {// Right turn
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Forward,
                                      turnSpeed,
                                      2,
                                      SH_Completion_Wait_For,
                                      SH_Next_Action_Brake);
    steerAngle = Brain::clamp(-60, steerAngle + 2, 60);
>>>>>>> origin/master
  }
}
*/

void Pilot::centerSteer()
{
  if(steerAngle < 0)
  {
    this->m_shield->bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 100, this->steerAngle, SH_Completion_Dont_Wait, SH_Next_Action_Brake);
    this->m_shield->bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 100, this->steerAngle, SH_Completion_Dont_Wait, SH_Next_Action_Brake);
  }
  else if(steerAngle >0)
  {
    this->m_shield->bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 100, this->steerAngle, SH_Completion_Dont_Wait, SH_Next_Action_Brake);
    this->m_shield->bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 100, this->steerAngle, SH_Completion_Dont_Wait, SH_Next_Action_Brake);
  }
  
  this->steerAngle = 0;

  return;
}

void Pilot::zeroSteer()
{
  this->m_shield->bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 100, 120, SH_Completion_Wait_For, SH_Next_Action_Float);
  this->m_shield->bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Forward, 100, 120, SH_Completion_Wait_For, SH_Next_Action_Float);

  delay(500);
  
  this->m_shield->bank_a.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 100, 60, SH_Completion_Wait_For, SH_Next_Action_Brake);
  this->m_shield->bank_b.motorRunDegrees(SH_Motor_1, SH_Direction_Reverse, 100, 60, SH_Completion_Wait_For, SH_Next_Action_Brake);

  return;
}
