#include "JoystickDrive.h"
#include "MrinalsControlLoop.h"

JoystickDrive::JoystickDrive() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize() {
	//if (Robot::tMode == Robot::TestMode::DRIVE_SPEED)
	//	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	//else
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		RobotMap::driverDrive1->SetCloseLoopRampRate(2.5);
		RobotMap::driverDrive1->SetCloseLoopRampRate(2.5);
}

// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute() {
	SmartDashboard::PutNumber("fudgefactor", RobotMap::driverDrive1->GetSetpoint() / Robot::drive->GetREncoderRate());
	Robot::drive->TankDrive(Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL()) * 800, Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR()) * 800, false);
	//if (Robot::tMode == Robot::TestMode::DRIVE_SPEED)
	//{
	//	SmartDashboard::PutNumber("test_speed_error", RobotMap::driverDrive1->GetClosedLoopError());
	//	SmartDashboard::PutNumber("test_speed_speed", RobotMap::driverDrive1->GetSetpoint());
	//}
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
