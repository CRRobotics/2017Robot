#include "SpeedProfileReplay.h"
#include "../../MrinalsControlLoop.h"

SpeedProfileReplay::SpeedProfileReplay(std::string replayName) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	rName = replayName;
}

// Called just before this Command runs the first time
void SpeedProfileReplay::Initialize() {
	MrinalsControlLoop::pMode = MrinalsControlLoop::PlayMode::SPEED_PROFILE;
	MrinalsControlLoop::inputFileName = SmartDashboard::GetString("input_file_name", "nameless.txt");//rName;
	if (!MrinalsControlLoop::running)
		MrinalsControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void SpeedProfileReplay::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedProfileReplay::IsFinished() {
	return !MrinalsControlLoop::running || MrinalsControlLoop::pMode != MrinalsControlLoop::PlayMode::SPEED_PROFILE;
}

// Called once after isFinished returns true
void SpeedProfileReplay::End() {
	MrinalsControlLoop::pMode = MrinalsControlLoop::PlayMode::NONE;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedProfileReplay::Interrupted() {
	MrinalsControlLoop::pMode = MrinalsControlLoop::PlayMode::NONE;
}
