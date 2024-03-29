#include "ShiftHigh.h"

ShiftHigh::ShiftHigh()
{
	// Use Requires() here to declare subsystem dependencies
}

// Called just before this Command runs the first time
void ShiftHigh::Initialize()
{
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	Robot::drive->SetDriveRampRate(3.0);
}

// Called repeatedly when this Command is scheduled to run
void ShiftHigh::Execute()
{
	Robot::drive->ChangeGear(true);
}

// Make this return true when this Command no longer needs to run execute()
bool ShiftHigh::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShiftHigh::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShiftHigh::Interrupted()
{

}
