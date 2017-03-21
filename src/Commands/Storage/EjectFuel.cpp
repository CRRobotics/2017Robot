#include "EjectFuel.h"

EjectFuel::EjectFuel()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::storage.get());
}

// Called just before this Command runs the first time
void EjectFuel::Initialize()
{
	Robot::storage->SetControlMode(CANTalon::ControlMode::kPercentVbus);//TODO change to kSpeed
}

// Called repeatedly when this Command is scheduled to run
void EjectFuel::Execute()
{
	Robot::storage->MoveStorage(1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool EjectFuel::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void EjectFuel::End()
{
	Robot::storage->MoveStorage(0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EjectFuel::Interrupted()
{
	Robot::storage->MoveStorage(0.0);

}
