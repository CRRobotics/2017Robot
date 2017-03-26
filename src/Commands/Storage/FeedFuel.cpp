#include "FeedFuel.h"

FeedFuel::FeedFuel()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::storage.get());
}

// Called just before this Command runs the first time
void FeedFuel::Initialize()
{
	Robot::storage->SetControlMode(CANTalon::ControlMode::kPercentVbus);//TODO change to kSpeed
}

// Called repeatedly when this Command is scheduled to run
void FeedFuel::Execute()
{
	Robot::storage->MoveStorage(-1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool FeedFuel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void FeedFuel::End()
{
	Robot::storage->MoveStorage(0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FeedFuel::Interrupted()
{
	Robot::storage->MoveStorage(0.0);

}
