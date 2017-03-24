#include "Pilot.h"

Pilot:: Pilot(NXShield& nxt, NXTLight r_l, NXTLight l_l, NXTUS sonar){
  pnxshield = &nxt;
  brain.setLeftLight(l_l);
  brain.setRightLight(r_l);
  brain.setSonar(sonar);
  maxSpeed = 100;
}

Pilot:: Pilot(NXShield& nxt, NXTLight r_l, NXTLight l_l, NXTUS sonar, int ms){
  pnxshield = &nxt;
  brain.setLeftLight(&l_l);
  brain.setRightLight(&r_l);
  brain.setSonar(&sonar);
  maxSpeed = ms;
}

// Full driving functionality
void Pilot::drive(int initialSpeed){
  setSpeed(initialSpeed);
  brain.think();
  
}

void Pilot::fullStop(){
  pnxshield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
}

void Pilot::slowStop(){
  int currentSpeed = brain.motorReal;
  while(currentSpeed >= 1){
    currentSpeed = currentSpeed - (currentSpeed/8);
    pnxshield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, currentSpeed);
    delay(50);
  }
  pnxshield->bank_a.motorStop(SH_Motor_1, SH_Next_Action_Brake);
}

void Pilot::setSpeed(int s){
  int currentSpeed = brain.motorReal;
  if(s > maxSpeed || s == -1) 
    currentSpeed = maxSpeed;
   else
    currentSpeed = s;
  brain.motorReal = s;
  // Set drive motor running
  pnxshield->bank_a.motorRunUnlimited(SH_Motor_1, SH_Direction_Forward, currentSpeed);
  
}

// Recieves a degree amount to turn; left degrees are negative, right are positive;
// Degree 0 is at center steer
void Pilot::turn(int turnDelta, int turnSpeed){
  int turnAngle = steerAngle + turnDelta;
  // Make sure no overturning
  if(turnAngle < -60){
    turnDelta = -60  - steerAngle;
    steerAngle = -60;
  } else if(turnAngle > 60){
    turnDelta = 60 - steerAngle;
    steerAngle = 60;
  }else {
    steerAngle = steerAngle + turnDelta;
  }
  
  if(turnDelta <0){
   pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Reverse, 
                                      turnSpeed, 
                                      abs(turnDelta), 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
  }else if(turnDelta > 0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Forward, 
                                      turnSpeed, 
                                      abs(turnDelta), 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
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
