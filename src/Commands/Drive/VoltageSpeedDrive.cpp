#include "VoltageSpeedDrive.h"

VoltageSpeedDrive::VoltageSpeedDrive(double v)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	voltage = v;
}

// Called just before this Command runs the first time
void VoltageSpeedDrive::Initialize()
{
	RobotMap::driverDrive1->SetControlMode(CANTalon::ControlMode::kVoltage);
	RobotMap::drivelDrive1->SetControlMode(CANTalon::ControlMode::kVoltage);
}

// Called repeatedly when this Command is scheduled to run
void VoltageSpeedDrive::Execute()
{
	Robot::drive->TankDrive(voltage, voltage);
}

// Make this return true when this Command no longer needs to run execute()
bool VoltageSpeedDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void VoltageSpeedDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VoltageSpeedDrive::Interrupted()
{

}
