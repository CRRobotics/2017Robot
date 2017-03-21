#include "FullProfileReplay.h"

FullProfileReplay::FullProfileReplay()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::gear.get());
	Requires(Robot::drive.get());
	Requires(Robot::acquisition.get());
	Requires(Robot::storage.get());
	Requires(Robot::shooter.get());
	Requires(Robot::climbing.get());
}

// Called just before this Command runs the first time
void FullProfileReplay::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void FullProfileReplay::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool FullProfileReplay::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void FullProfileReplay::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FullProfileReplay::Interrupted()
{

}
