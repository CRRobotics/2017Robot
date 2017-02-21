#include <Commands/Shooter/RunShooter.h>

RunShooter::RunShooter() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RunShooter::Initialize() {
	Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kSpeed);
}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
	if (!Robot::shooter->IsRunning()) //Toggle the shooter flywheel
		Robot::shooter->RunFlywheel(GetDesiredSpeed());
	else
		Robot::shooter->RunFlywheel(0);
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooter::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void RunShooter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooter::Interrupted() {

}

double RunShooter::GetDesiredSpeed(){
	if (Robot::tMode == Robot::TestMode::SHOOTER_SPEED)
		return SmartDashboard::GetNumber("test_setPoint", 0);
	else
		return 600;
}
