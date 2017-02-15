#include "GearOut.h"

GearOut::GearOut() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void GearOut::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearOut::Execute() {
	Robot::gear->ExtendGear();
}

// Make this return true when this Command no longer needs to run execute()
bool GearOut::IsFinished() {
	return Robot::gear->GetExtended();
}

// Called once after isFinished returns true
void GearOut::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearOut::Interrupted() {

}
