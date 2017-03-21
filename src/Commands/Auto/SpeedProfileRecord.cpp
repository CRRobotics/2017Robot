#include <CustomControlLoop.h>
#include "SpeedProfileRecord.h"

SpeedProfileRecord::SpeedProfileRecord()
{

}

// Called just before this Command runs the first time
void SpeedProfileRecord::Initialize()
{
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::SPEED_PROFILE;
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
	CustomControlLoop::outputFileName = SmartDashboard::GetString("output_file_name", "nameless.csv");
	if (!CustomControlLoop::running)
		CustomControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void SpeedProfileRecord::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedProfileRecord::IsFinished()
{
	return !CustomControlLoop::running || CustomControlLoop::rMode == CustomControlLoop::RecordMode::NONE;
}

// Called once after isFinished returns true
void SpeedProfileRecord::End()
{
	//CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
	CustomControlLoop::running = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedProfileRecord::Interrupted()
{
	//CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
	CustomControlLoop::running = false;
}
