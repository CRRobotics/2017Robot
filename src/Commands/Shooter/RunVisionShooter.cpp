#include <Commands/Shooter/RunVisionShooter.h>
bool RunVisionShooter::running;

double RunVisionShooter::lastDistance = 0;

RunVisionShooter::RunVisionShooter()
{
	Requires(Robot::shooter.get());
	running = false;

}

// Called just before this Command runs the first time
void RunVisionShooter::Initialize()
{
	Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void RunVisionShooter::Execute()
{
	if (!running)
		Robot::shooter->RunFlywheel(GetDesiredSpeed());
	else
		Robot::shooter->RunFlywheel(0);
}

// Make this return true when this Command no longer needs to run execute()
bool RunVisionShooter::IsFinished()
{
	running = !running;
	return true;
}

// Called once after isFinished returns true
void RunVisionShooter::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunVisionShooter::Interrupted()
{

}

double RunVisionShooter::GetDesiredSpeed()
{
	if (Robot::table != nullptr)
		lastDistance = Robot::table->GetNumber("DistanceToBoiler", lastDistance);
	return lastDistance;
}
