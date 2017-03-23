#include "GearOut.h"

GearOut::GearOut()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
	Requires(Robot::acquisition.get());
}

// Called just before this Command runs the first time
void GearOut::Initialize()
{
	Robot::acquisition->CloseHopper();
}

// Called repeatedly when this Command is scheduled to run
void GearOut::Execute()
{
	Robot::acquisition->CloseHopper();
	Robot::gear->ExtendGear();
}

// Make this return true when this Command no longer needs to run execute()
bool GearOut::IsFinished()
{
	return false;//Robot::gear->GetExtended();
}

// Called once after isFinished returns true
void GearOut::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearOut::Interrupted()
{

}
