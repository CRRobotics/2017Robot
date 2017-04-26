#include <Commands/FloorAcq/PickUpFloorGear.h>
#include "../LEDs/LEDRefresh.h"
#define MODE_DELAY 15

PickUpFloorGear::PickUpFloorGear()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
	Requires(Robot::floorAcq.get());
	Requires(Robot::acquisition.get());
	drop_ticker = 0;
	mode = 0;
	firstTime = true;
}

// Called just before this Command runs the first time
void PickUpFloorGear::Initialize()
{
	Robot::acquisition->CloseHopper();
	Robot::gear->RetractGear();
	if (!firstTime)
		Robot::floorAcq->OpenSystem();
	Robot::floorAcq->LowerSystem();
	drop_ticker = 0;
	mode = 0;
}

// Called repeatedly when this Command is scheduled to run
void PickUpFloorGear::Execute()
{
	Robot::acquisition->CloseHopper();
	if (!Robot::oi->GetFloorGear())
		mode = 3;
	if (mode == 0)
	{
		if (drop_ticker < MODE_DELAY)
			Robot::floorAcq->LowerSystem();
		else
		{
			mode++;
			drop_ticker = 0;
			Robot::floorAcq->OpenSystem();
			firstTime = false;
		}
	}
	else if (mode == 1)
	{
		if (drop_ticker < MODE_DELAY)
			Robot::floorAcq->OpenSystem();
		else
			mode++;
	}
	else if (mode == 2)
	{
		if (Robot::floorAcq->GearPresent())
		{
			LEDRefresh::SetMode(LEDs::LEDMode::GREEN_BLINK, 4000);
			Robot::floorAcq->CloseSystem();
			drop_ticker = 0;
			mode++;
		}
	}
	else if (mode == 3)
	{
		if (drop_ticker < MODE_DELAY)
			Robot::floorAcq->CloseSystem();
		else
		{
			mode++;
			Robot::floorAcq->RaiseSystem();
		}
	}
	drop_ticker++;
}

// Make this return true when this Command no longer needs to run execute()
bool PickUpFloorGear::IsFinished()
{
	return mode == 4;
}

// Called once after isFinished returns true
void PickUpFloorGear::End()
{
	Robot::floorAcq->CloseSystem();
	Robot::floorAcq->RaiseSystem();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PickUpFloorGear::Interrupted()
{
	Robot::floorAcq->CloseSystem();
	Robot::floorAcq->RaiseSystem();
}
