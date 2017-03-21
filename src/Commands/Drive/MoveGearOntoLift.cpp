#include "MoveGearOntoLift.h"
#include "Robot.h"

MoveGearOntoLift::MoveGearOntoLift()
{
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void MoveGearOntoLift::Initialize()
{
	Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
	ticker = 0;
}

// Called repeatedly when this Command is scheduled to run
void MoveGearOntoLift::Execute()
{
	if (ticker % 20 < 10)
		Robot::drive->TankDrive(0.2, 0.3);
	else
		Robot::drive->TankDrive(0.3, 0.2);
	ticker++;
}

// Make this return true when this Command no longer needs to run execute()
bool MoveGearOntoLift::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void MoveGearOntoLift::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveGearOntoLift::Interrupted()
{

}
