#include "GearOutWithSensor.h"

GearOutWithSensor::GearOutWithSensor()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
	Requires(Robot::acquisition.get());
}

// Called just before this Command runs the first time
void GearOutWithSensor::Initialize()
{
	Robot::acquisition->CloseHopper();
}

// Called repeatedly when this Command is scheduled to run
void GearOutWithSensor::Execute()
{
	Robot::acquisition->CloseHopper();
	if (Robot::gear->PegPresent())
		Robot::gear->ExtendGear();
}

// Make this return true when this Command no longer needs to run execute()
bool GearOutWithSensor::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void GearOutWithSensor::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearOutWithSensor::Interrupted()
{

}
