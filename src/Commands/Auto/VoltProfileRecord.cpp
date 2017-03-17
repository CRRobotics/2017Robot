#include "VoltProfileRecord.h"
#include "../../MrinalsControlLoop.h"

VoltProfileRecord::VoltProfileRecord() {

}

// Called just before this Command runs the first time
void VoltProfileRecord::Initialize() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::VOLT_PROFILE;
	MrinalsControlLoop::outputFileName = SmartDashboard::GetString("output_file_name", "nameless.csv");
	if (!MrinalsControlLoop::running)
		MrinalsControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void VoltProfileRecord::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool VoltProfileRecord::IsFinished() {
	return !MrinalsControlLoop::running || MrinalsControlLoop::rMode == MrinalsControlLoop::RecordMode::NONE;
}

// Called once after isFinished returns true
void VoltProfileRecord::End() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::NONE;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VoltProfileRecord::Interrupted() {
	MrinalsControlLoop::rMode = MrinalsControlLoop::RecordMode::NONE;
}
