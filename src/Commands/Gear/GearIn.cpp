#include "GearIn.h"

GearIn::GearIn()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
}

// Called just before this Command runs the first time
void GearIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void GearIn::Execute()
{
	Robot::gear->RetractGear();
}

// Make this return true when this Command no longer needs to run execute()
bool GearIn::IsFinished()
{
	return false;//!Robot::gear->GetExtended();
}

// Called once after isFinished returns true
void GearIn::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearIn::Interrupted()
{

}
