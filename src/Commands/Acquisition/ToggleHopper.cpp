#include "ToggleHopper.h"

ToggleHopper::ToggleHopper() {
}

// Called just before this Command runs the first time
void ToggleHopper::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ToggleHopper::Execute() {
	if(RobotMap::doorPiston->Get() == true) {
		Robot::acquisition->CloseHopper();
	}
	else
	{
		Robot::acquisition->OpenHopper();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleHopper::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ToggleHopper::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleHopper::Interrupted() {

}
