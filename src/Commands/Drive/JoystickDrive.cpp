#include <CustomControlLoop.h>
#include "JoystickDrive.h"

JoystickDrive::JoystickDrive()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize()
{
	if (Robot::drive->BothEncodersPresent())
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		Robot::drive->SetDriveRampRate(3.0);
	}
	else
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
}

// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute()
{
	SmartDashboard::PutNumber("fudgefactor", RobotMap::driverDrive1->GetSetpoint() / Robot::drive->GetREncoderRate());
	Robot::drive->TankDrive(Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL()), Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR()), true);
	//if (Robot::tMode == Robot::TestMode::DRIVE_SPEED)
	//{
	//	SmartDashboard::PutNumber("test_speed_error", RobotMap::driverDrive1->GetClosedLoopError());
	//	SmartDashboard::PutNumber("test_speed_speed", RobotMap::driverDrive1->GetSetpoint());
	//}
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickDrive::Interrupted()
{

}
