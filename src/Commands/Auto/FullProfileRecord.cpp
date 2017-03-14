#include "FullProfileRecord.h"

FullProfileRecord::FullProfileRecord() {

}

// Called just before this Command runs the first time
void FullProfileRecord::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void FullProfileRecord::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool FullProfileRecord::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void FullProfileRecord::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FullProfileRecord::Interrupted() {

}
