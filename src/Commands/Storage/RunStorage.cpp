#include "RunStorage.h"
#define SHOOTER_ACCEPTABLE_ERROR 50

RunStorage::RunStorage() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void RunStorage::Initialize() {
	Robot::storage->SetControlMode(CANTalon::ControlMode::kVoltage);//TODO change to kSpeed
}

// Called repeatedly when this Command is scheduled to run
void RunStorage::Execute() {
	if (fabs(Robot::shooter->GetFlywheelSpeed() - RunShooter::GetDesiredSpeed()) < SHOOTER_ACCEPTABLE_ERROR){
		Robot::storage->MoveStorage(0.3);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RunStorage::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RunStorage::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunStorage::Interrupted() {

}
