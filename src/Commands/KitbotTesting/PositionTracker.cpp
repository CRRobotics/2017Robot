#include "PositionTracker.h"

PositionTracker::PositionTracker()
{
	Requires(Robot::gear.get()); //Don't let controller confuse the robot by mashing both buttons
}

// Called just before this Command runs the first time
void PositionTracker::Initialize()
{
	xPos = 0.0;
	yPos = 0.0;
	lastTime = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

}

// Called repeatedly when this Command is scheduled to run
void PositionTracker::Execute()
{
	long currentTime = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	long timeInterval = currentTime - lastTime;
	lastTime = currentTime;
	double curV = (RobotMap::driverDrive1->GetSpeed() + RobotMap::drivelDrive1->GetSpeed()) / 2;
	xPos += curV * cos(Robot::drive->GetYaw() * 3.141592 / 180) * 6 * 3.141592 * (timeInterval / 1000.0 / 60.0);
	yPos += curV * sin(Robot::drive->GetYaw() * 3.141592 / 180) * 6 * 3.141592 * (timeInterval / 1000.0 / 60.0);
	//printf("%f\n", curV);
	SmartDashboard::PutNumber("x_pos", xPos);
	SmartDashboard::PutNumber("y_pos", yPos);
}

// Make this return true when this Command no longer needs to run execute()
bool PositionTracker::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PositionTracker::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionTracker::Interrupted()
{

}
