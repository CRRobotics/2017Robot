#include "SpeedProfileRecord.h"
#include "../../MrinalsControlLoop.h"

SpeedProfileRecord::SpeedProfileRecord() {

}

// Called just before this Command runs the first time
void SpeedProfileRecord::Initialize() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::SPEED_PROFILE;
	MrinalsControlLoop::outputFileName = SmartDashboard::GetString("output_file_name", "nameless.csv");
	if (!MrinalsControlLoop::running)
		MrinalsControlLoop::Loop();
}

// Called repeatedly when this Command is scheduled to run
void SpeedProfileRecord::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedProfileRecord::IsFinished() {
	return !MrinalsControlLoop::running || MrinalsControlLoop::rMode != MrinalsControlLoop::RecordMode::NONE;
}

// Called once after isFinished returns true
void SpeedProfileRecord::End() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::NONE;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedProfileRecord::Interrupted() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::NONE;
}
