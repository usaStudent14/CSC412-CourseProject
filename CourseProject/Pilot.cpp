#include "Pilot.h"

Pilot:: Pilot(NXShield& nxt, NXTLight& r_l, NXTLight& c_l, NXTLight& l_l, NXTUS& sonar){
  pnxshield = &nxt;
  brain.m_leftLight = &l_l;
  brain.m_centerLight = &c_l;
  brain.m_rightLight = &r_l;
  brain.m_sonar = &sonar;
  currentSpeed = 0;
  steerAngle = 0;
  maxSpeed = 100;
}

Pilot:: Pilot(NXShield& nxt, NXTLight& r_l, NXTLight& c_l, NXTLight& l_l, NXTUS& sonar, int ms){
  pnxshield = &nxt;
  brain.m_leftLight = &l_l;
  brain.m_centerLight = &c_l;
  brain.m_rightLight = &r_l;
  brain.m_sonar = &sonar;
  currentSpeed = 0;
  steerAngle = 0;
  maxSpeed = ms;
}

// Full driving functionality
void Pilot::drive(int initialSpeed){
  setSpeed(initialSpeed);
  brain.think();

  turn(brain.targetHeading, 100);
}

void Pilot::fullStop(){
  pnxshield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
}

void Pilot::slowStop(){
  while(currentSpeed >= 1){
    currentSpeed = currentSpeed - (currentSpeed/8);
    pnxshield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, currentSpeed);
    delay(50);
  }
  pnxshield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
}

void Pilot::setSpeed(int s){
  if(s > maxSpeed || s == -1) 
    currentSpeed = maxSpeed;
   else
    currentSpeed = s;
  // Set drive motor running
  pnxshield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, currentSpeed);
  
}

// Recieves a degree amount to turn; left degrees are negative, right are positive;
// Degree 0 is at center steer
void Pilot::turn(int heading, int turnSpeed){
  if((heading < steerAngle)) {// Left turn
   pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Reverse, 
                                      turnSpeed, 
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
  }
}

void Pilot::centerSteer(){
  if(steerAngle < 0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Forward, 
                                    100, 
                                    steerAngle, 
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake); 
  }else if(steerAngle >0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Reverse, 
                                    100, 
                                    steerAngle, 
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake); 
  }
  steerAngle = 0;
}

void Pilot::zeroSteer(){
  pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Forward, 
                                    100,
                                    120, 
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_Float);
  delay(500);
  pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Reverse, 
                                    100, 
                                    60, 
                                    SH_Completion_Wait_For,
                                    SH_Next_Action_Brake); 
}

void Pilot::setMaxSpeed(int ms){
  maxSpeed = ms;
}

int Pilot::getMaxSpeed(){
  return maxSpeed;
}

void Pilot::resetMotors()
{
  pnxshield->bank_a.motorReset();
}
