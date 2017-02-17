#include "FireShooter.h"

FireShooter::FireShooter() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void FireShooter::Initialize() {
	Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void FireShooter::Execute() {
	Robot::shooter->RunFlywheel(GetDesiredSpeed());
}

// Make this return true when this Command no longer needs to run execute()
bool FireShooter::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FireShooter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireShooter::Interrupted() {

}

double FireShooter::GetDesiredSpeed(){
	if (Robot::tMode == Robot::TestMode::SHOOTER_SPEED)
		return SmartDashboard::GetNumber("test_setPoint", 0);
	else
		return 600;
}
