#include "AcquisitionIn.h"

AcquisitionIn::AcquisitionIn() {
	Requires(Robot::acquisition.get());
}

// Called just before this Command runs the first time
void AcquisitionIn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AcquisitionIn::Execute() {
	//Robot::acquisition->Intake();
	//Robot::acquisition->LowerArm();
}

// Make this return true when this Command no longer needs to run execute()
bool AcquisitionIn::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AcquisitionIn::End() {
	//Robot::acquisition->Stop();
	//Robot::acquisition->RaiseArm();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AcquisitionIn::Interrupted() {

}
