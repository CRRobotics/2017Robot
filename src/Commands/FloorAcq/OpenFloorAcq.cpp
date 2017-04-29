#include <Commands/FloorAcq/OpenFloorAcq.h>
#include "../LEDs/LEDRefresh.h"
#define MODE_DELAY 15

OpenFloorAcq::OpenFloorAcq()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
	Requires(Robot::floorAcq.get());
	Requires(Robot::acquisition.get());
}

// Called just before this Command runs the first time
void OpenFloorAcq::Initialize()
{
	Robot::floorAcq->OpenSystem();
}

// Called repeatedly when this Command is scheduled to run
void OpenFloorAcq::Execute()
{
	Robot::floorAcq->OpenSystem();
}

// Make this return true when this Command no longer needs to run execute()
bool OpenFloorAcq::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OpenFloorAcq::End()
{
	Robot::floorAcq->CloseSystem();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenFloorAcq::Interrupted()
{
	Robot::floorAcq->CloseSystem();
}
