#include "AcquisitionIn.h"

AcquisitionIn::AcquisitionIn() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::storage.get());
}

// Called just before this Command runs the first time
void AcquisitionIn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AcquisitionIn::Execute() {
	Robot::acquisition->Intake();
}

// Make this return true when this Command no longer needs to run execute()
bool AcquisitionIn::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AcquisitionIn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AcquisitionIn::Interrupted() {

}
