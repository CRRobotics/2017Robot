#include "RunStorage.h"

RunStorage::RunStorage() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::storage.get());
}

// Called just before this Command runs the first time
void RunStorage::Initialize() {
	Robot::storage->SetControlMode(CANTalon::ControlMode::kPercentVbus);//TODO change to kSpeed
}

// Called repeatedly when this Command is scheduled to run
void RunStorage::Execute() {
	//Either Acquisition is running or the shooter is sunning and ready to fire
	if (Robot::oi->GetAcquisition()){
		printf("Storage running\n");
		Robot::storage->MoveStorage(1.0);
	}
	else if (Robot::oi->GetFiring() && Robot::shooter->UpToSpeed()){
		//double speed = fabs (30.0 / Robot::shooter->GetSpeedError());
		Robot::storage->MoveStorage(-0.8);
	}
	else {
		Robot::storage->MoveStorage(0.0);
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
