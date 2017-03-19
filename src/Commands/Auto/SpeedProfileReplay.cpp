#include <CustomControlLoop.h>
#include "SpeedProfileReplay.h"

SpeedProfileReplay::SpeedProfileReplay(std::string replayName) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	rName = replayName;
}

// Called just before this Command runs the first time
void SpeedProfileReplay::Initialize() {
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::SPEED_PROFILE;
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
	CustomControlLoop::inputFileName = SmartDashboard::GetString("input_file_name", "nameless.txt");//rName;
	if (!CustomControlLoop::running)
		CustomControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void SpeedProfileReplay::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedProfileReplay::IsFinished() {
	return !CustomControlLoop::running || CustomControlLoop::pMode != CustomControlLoop::PlayMode::SPEED_PROFILE;
}

// Called once after isFinished returns true
void SpeedProfileReplay::End() {
	//CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
	CustomControlLoop::running = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedProfileReplay::Interrupted() {
	//CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
	CustomControlLoop::running = false;
}
