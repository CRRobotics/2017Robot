#include "StopClimber.h"

StopClimber::StopClimber()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void StopClimber::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StopClimber::Execute()
{
	Robot::climbing->UnLockMotor();
}

// Make this return true when this Command no longer needs to run execute()
bool StopClimber::IsFinished()
{
	return !Robot::climbing->IsMotorLocked();
}

// Called once after isFinished returns true
void StopClimber::End()
{
	//Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopClimber::Interrupted()
{

}
