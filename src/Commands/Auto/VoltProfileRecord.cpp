#include <CustomControlLoop.h>
#include "VoltProfileRecord.h"

VoltProfileRecord::VoltProfileRecord() {

}

// Called just before this Command runs the first time
void VoltProfileRecord::Initialize() {
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::VOLT_PROFILE;
	CustomControlLoop::outputFileName = SmartDashboard::GetString("output_file_name", "nameless.csv");
	if (!CustomControlLoop::running)
		CustomControlLoop::StartLoop();
}

// Called repeatedly when this Command is scheduled to run
void VoltProfileRecord::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool VoltProfileRecord::IsFinished() {
	return !CustomControlLoop::running || CustomControlLoop::rMode == CustomControlLoop::RecordMode::NONE;
}

// Called once after isFinished returns true
void VoltProfileRecord::End() {
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VoltProfileRecord::Interrupted() {
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
}
