#include <Commands/Shooter/FireBallsLow.h>

FireBallsLow::FireBallsLow() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void FireBallsLow::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void FireBallsLow::Execute() {
	Robot::shooter->SetAngle(false);
	if (Robot::shooter->UpToSpeed()) //Is the shooter up to speed?
		Robot::shooter->SetGatePosition(false); //TODO make the shooter alternate sides while held
	else
		Robot::shooter->SetGatePosition(true);
}

// Make this return true when this Command no longer needs to run execute()
bool FireBallsLow::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void FireBallsLow::End() {
	Robot::shooter->SetGatePosition(true);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireBallsLow::Interrupted() {

}

