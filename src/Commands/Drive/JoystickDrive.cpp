#include "JoystickDrive.h"

JoystickDrive::JoystickDrive() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize() {
	if (Robot::tMode == Robot::TestMode::DRIVE_SPEED)
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	else
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
}

// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute() {
	Robot::drive->TankDrive(Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL()), Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR()), Robot::tMode == Robot::TestMode::DRIVE_SPEED);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JoystickDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickDrive::Interrupted() {

}
