#include "ShiftLow.h"

ShiftLow::ShiftLow()
{
	// Use Requires() here to declare subsystem dependencies
}

// Called just before this Command runs the first time
void ShiftLow::Initialize()
{
	Robot::drive->SetPIDF(0.6, 0.0,0.0, 0.15);
	Robot::drive->SetDriveRampRate(1.0);
}

// Called repeatedly when this Command is scheduled to run
void ShiftLow::Execute()
{
	Robot::drive->ChangeGear(false);
}

// Make this return true when this Command no longer needs to run execute()
bool ShiftLow::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ShiftLow::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShiftLow::Interrupted()
{

}
