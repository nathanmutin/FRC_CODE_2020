/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnToPoint.h"

TurnToPoint::TurnToPoint(DriveTrain* driveTrain, float x, float y) : m_driveTrain{driveTrain}, m_targetX{x}, m_targetY{y} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({driveTrain});
}

// Called when the command is initially scheduled.
void TurnToPoint::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void TurnToPoint::Execute() {
  double diffX = m_targetX - m_driveTrain->m_botX;
  double diffY = m_targetY - m_driveTrain->m_botY;
  m_driveTrain->m_turnPID.setSetPoint(getAngle(diffX, diffY));
  double v = m_driveTrain->m_turnPID.calculate(m_driveTrain->m_botDirection);
  m_driveTrain->tankDrive(-v, v);
}

// Called once the command ends or is interrupted.
void TurnToPoint::End(bool interrupted) {}

// Returns true when the command should end.
bool TurnToPoint::IsFinished() { 
  return std::abs(m_driveTrain->m_turnPID.calculate(m_driveTrain->m_botDirection)) < 0.05;
}

double TurnToPoint::getAngle(double x, double y) {
  double angle;
  if(x == 0 && y == 0) {
    angle = 0;
  } else {
    angle = std::atan(x / y);
  }
  if(y < 0 && x >= 0){
    angle += M_PI;
  } else if(y < 0 && x < 0){
    angle += M_PI;
    angle = -angle;
  }
  return angle;
}