#include <Commands/Shooter/StopShooter.h>

StopShooter::StopShooter()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void StopShooter::Initialize()
{
	Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kPercentVbus);
}

// Called repeatedly when this Command is scheduled to run
void StopShooter::Execute()
{
	Robot::shooter->RunFlywheel(0);
}

// Make this return true when this Command no longer needs to run execute()
bool StopShooter::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void StopShooter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShooter::Interrupted()
{

}

