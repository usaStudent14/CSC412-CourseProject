#include "Pilot.h"

Pilot:: Pilot(NXShield& nxt){
  pnxshield = &nxt;
  maxSpeed = 100;
  currentSpeed = 0;
  steerAngle = 0;
}

Pilot:: Pilot(NXShield& nxt, int ms){
  pnxshield = &nxt;
  maxSpeed = ms;
  currentSpeed = 0;
  steerAngle = 0;
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

void Pilot::driveAtSpeed(int s){
  if(s > maxSpeed || s == -1) 
    currentSpeed = maxSpeed;
   else
    currentSpeed = s;
  
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
                                      turnDelta, 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
  }else if(turnDelta > 0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                      SH_Direction_Forward, 
                                      turnSpeed, 
                                      turnDelta, 
                                      SH_Completion_Dont_Wait,
                                      SH_Next_Action_Brake);
  }
}

void Pilot::centerSteer(){
  if(steerAngle < 0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Forward, 
                                    currentSpeed/2, 
                                    steerAngle, 
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake); 
  }else if(steerAngle >0){
    pnxshield->bank_a.motorRunDegrees(SH_Motor_2, 
                                    SH_Direction_Reverse, 
                                    currentSpeed/2, 
                                    steerAngle, 
                                    SH_Completion_Dont_Wait,
                                    SH_Next_Action_Brake); 
  }
  steerAngle = 0;
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
