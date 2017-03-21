#include "DriveForwardAtSpeed.h"
#include "Robot.h"

DriveForwardAtSpeed::DriveForwardAtSpeed(double s)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	speed = s;
}

// Called just before this Command runs the first time
void DriveForwardAtSpeed::Initialize()
{
	//Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	RobotMap::drivelDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
	RobotMap::driverDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
	RobotMap::drivelDrive1->SetPID(0.7, 0.0, 0.0, 0.0);
	RobotMap::driverDrive1->SetPID(0.7, 0.0, 0.0, 0.0);
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardAtSpeed::Execute()
{
	Robot::drive->TankDrive(speed, speed);
	//printf("%d\n",(RobotMap::drivelDrive1->GetSpeed()));

}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardAtSpeed::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveForwardAtSpeed::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardAtSpeed::Interrupted()
{

}
