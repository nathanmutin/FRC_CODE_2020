/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LowerElevator.h"

LowerElevator::LowerElevator(Climb* climb, std::function<double()> getZ, std::function<bool()> end) : m_climb{climb}, m_getZ{getZ}, m_shouldEnd{end} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({climb});
}

// Called when the command is initially scheduled.
void LowerElevator::Initialize() {
  m_climb->setMotor(constant::KEEP_ELEVATOR_LEVEL_VALUE);
}

void LowerElevator::Execute() {
  m_climb->setMotor(m_getZ());
}

// Called once the command ends or is interrupted.
void LowerElevator::End(bool interrupted) {
  m_climb->setMotor(constant::KEEP_ELEVATOR_LEVEL_VALUE);
}

// Returns true when the command should end.
bool LowerElevator::IsFinished() { return m_shouldEnd(); }
