#include "MoveGearOntoLift.h"
#include "Robot.h"

MoveGearOntoLift::MoveGearOntoLift() {
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void MoveGearOntoLift::Initialize() {
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	ticker = 0;
}

// Called repeatedly when this Command is scheduled to run
void MoveGearOntoLift::Execute() {
	if (ticker % 20 < 10)
		Robot::drive->TankDrive(500, 600);
	else
		Robot::drive->TankDrive(600, 500);
	SmartDashboard::PutNumber("test_speed_error", RobotMap::driverDrive1->GetClosedLoopError());
	SmartDashboard::PutNumber("test_speed_speed", RobotMap::driverDrive1->GetEncVel());
	ticker++;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveGearOntoLift::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveGearOntoLift::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveGearOntoLift::Interrupted() {

}
