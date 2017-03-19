#include <CustomControlLoop.h>
#include "VoltProfileReplay.h"

VoltProfileReplay::VoltProfileReplay(std::string replayName) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	rName = replayName;
}

// Called just before this Command runs the first time
void VoltProfileReplay::Initialize() {
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::VOLT_PROFILE;
	CustomControlLoop::inputFileName = SmartDashboard::GetString("input_file_name", "nameless.txt");//rName;
	if (!CustomControlLoop::running)
		CustomControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void VoltProfileReplay::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool VoltProfileReplay::IsFinished() {
	return !CustomControlLoop::running || CustomControlLoop::pMode != CustomControlLoop::PlayMode::VOLT_PROFILE;
}

// Called once after isFinished returns true
void VoltProfileReplay::End() {
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VoltProfileReplay::Interrupted() {
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
}
