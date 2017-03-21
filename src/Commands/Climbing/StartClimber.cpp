#include "StartClimber.h"

StartClimber::StartClimber()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::climbing.get());
}

// Called just before this Command runs the first time
void StartClimber::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void StartClimber::Execute()
{
	Robot::climbing->LockMotor();
}

// Make this return true when this Command no longer needs to run execute()
bool StartClimber::IsFinished()
{
	return Robot::climbing->IsMotorLocked();
}

// Called once after isFinished returns true
void StartClimber::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StartClimber::Interrupted()
{

}
