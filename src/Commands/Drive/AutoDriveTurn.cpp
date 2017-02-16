#include "AutoDriveTurn.h"

AutoDriveTurn::AutoDriveTurn() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void AutoDriveTurn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveTurn::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveTurn::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoDriveTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveTurn::Interrupted() {

}
