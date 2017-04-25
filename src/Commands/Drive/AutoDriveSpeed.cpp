#include "AutoDriveSpeed.h"
#include "Robot.h"

AutoDriveSpeed::AutoDriveSpeed()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	speed = 0;
}

// Called just before this Command runs the first time
void AutoDriveSpeed::Initialize()
{
	speed = SmartDashboard::GetNumber("test_setPoint", 0.0);
	//if (Robot::drive->BothEncodersPresent())
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveSpeed::Execute()
{
	speed = SmartDashboard::GetNumber("test_setPoint", 0.0);
	Robot::drive->TankDrive(speed, speed);
	SmartDashboard::PutNumber("drive_speed_error_r", RobotMap::driverDrive1->GetClosedLoopError());
	SmartDashboard::PutNumber("drive_speed_error_l", RobotMap::drivelDrive1->GetClosedLoopError());

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveSpeed::IsFinished()
{
	//if (!Robot::drive->BothEncodersPresent())
	//	return true;
	return false;
}

// Called once after isFinished returns true
void AutoDriveSpeed::End()
{
	RobotMap::driverDrive1->ClearIaccum();
	RobotMap::drivelDrive1->ClearIaccum();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveSpeed::Interrupted()
{
	RobotMap::driverDrive1->ClearIaccum();
	RobotMap::drivelDrive1->ClearIaccum();
}
