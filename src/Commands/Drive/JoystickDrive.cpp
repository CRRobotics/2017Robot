#include <CustomControlLoop.h>
#include "JoystickDrive.h"

JoystickDrive::JoystickDrive()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	SmartDashboard::PutNumber("max_lSpeed", 0.0);
	SmartDashboard::PutNumber("max_rSpeed", 0.0);
}

// Called just before this Command runs the first time
void JoystickDrive::Initialize()
{
	if (Robot::drive->BothEncodersPresent())
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		Robot::drive->SetDriveRampRate(2.0);
	}
	else
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
}

// Called repeatedly when this Command is scheduled to run
void JoystickDrive::Execute()
{
	bool encodersPresent = Robot::drive->BothEncodersPresent();
	if (!encodersPresent)
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
	}
//	else if (encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::Voltage && !(Robot::climbing->IsMotorLocked()))
//	{
//		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
//		Robot::drive->SetDriveRampRate(3.0);
//	}

	//if (fabs(RobotMap::driverDrive1->GetEncVel()) > SmartDashboard::GetNumber("max_rSpeed", 0.0))
	//	SmartDashboard::PutNumber("max_rSpeed", fabs(RobotMap::driverDrive1->GetEncVel()));
	//if (fabs(RobotMap::drivelDrive1->GetEncVel()) > SmartDashboard::GetNumber("max_lSpeed", 0.0))
	//	SmartDashboard::PutNumber("max_lSpeed", fabs(RobotMap::drivelDrive1->GetEncVel()));
	Robot::drive->TankDrive(Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL()), Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR()), encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::VelocityDriving);
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
