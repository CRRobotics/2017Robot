#include <Commands/Shooter/FireBalls.h>

FireBalls::FireBalls(bool shootHigh) {
	high = shootHigh;
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void FireBalls::Initialize() {
	Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kPercentVbus);//kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void FireBalls::Execute() {
	Robot::shooter->RunFlywheel(1.0);//GetDesiredSpeed());
	Robot::shooter->SetAngle(high);
	if (Robot::shooter->UpToSpeed()) //Is the shooter up to speed?
		Robot::shooter->SetGatePosition(false); //TODO make the shooter alternate sides while held
	else
		Robot::shooter->SetGatePosition(true);
}

// Make this return true when this Command no longer needs to run execute()
bool FireBalls::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FireBalls::End() {
	Robot::shooter->SetGatePosition(true);
	Robot::shooter->RunFlywheel(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireBalls::Interrupted() {
	Robot::shooter->RunFlywheel(0.0);
}


double FireBalls::GetDesiredSpeed(){
	if (Robot::table != nullptr)
		lastDistance = Robot::table->GetNumber("DistanceToBoiler", lastDistance);
	return lastDistance;
}

