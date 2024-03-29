#include "RunStorage.h"

RunStorage::RunStorage()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::storage.get());
}

// Called just before this Command runs the first time
void RunStorage::Initialize()
{
	Robot::storage->SetControlMode(CANTalon::ControlMode::kPercentVbus);//TODO change to kSpeed
}

// Called repeatedly when this Command is scheduled to run
void RunStorage::Execute()
{
	//Either Acquisition is running or the shooter is sunning and ready to fire
	if (Robot::oi->GetAcquisition())
	{
		printf("Storage running\n");
		Robot::storage->MoveStorage(-1.0);
	}
	else if (Robot::oi->GetFiring())//!RobotMap::leftGate->Get() || !RobotMap::rightGate->Get()
	{
		if (Robot::shooter->UpToSpeed())
			Robot::storage->MoveStorage(-1.0);
		else
			Robot::storage->MoveStorage(1.0);
	}
	else {
		Robot::storage->MoveStorage(0.0);
	}
}

double speedAtShooterError(double e)
{
	if (fabs(e) > 2000)
		return -0.0;
	else if (fabs(e) < 1000)
		return -1.0;
	else
		return -1000 / ((fabs(e) + 2000) * 0.33333);
}

// Make this return true when this Command no longer needs to run execute()
bool RunStorage::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunStorage::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunStorage::Interrupted()
{

}
