#include "AutoDriveDistance.h"
#include "Robot.h"

AutoDriveDistance::AutoDriveDistance(double dist) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	desiredDist = dist;
}

// Called just before this Command runs the first time
void AutoDriveDistance::Initialize() {
	if (Robot::tMode == Robot::TestMode::DRIVE_POSITION)
	{
		desiredDist = SmartDashboard::GetNumber("test_setPoint", 0);
		maxSpeed = SmartDashboard::GetNumber("test_max_speed", 0);
		slowStart = SmartDashboard::GetNumber("test_slow_start", 0);
		slowEnd = SmartDashboard::GetNumber("test_slow_end", 0);
	}
	double avgEncTick = (Robot::drive->GetLEncoder() + Robot::drive->GetREncoder()) / 2.0;
	desiredEncTick = avgEncTick + desiredDist * ENC_PULSE_PER_IN;
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveDistance::Execute() {
	double avgEncTick = (Robot::drive->GetLEncoder() + Robot::drive->GetREncoder()) / 2.0;
	double error = desiredEncTick - avgEncTick;
	if (error > slowStart)
		Robot::drive->TankDrive(maxSpeed, maxSpeed, true);
	else if (error > slowEnd)
		Robot::drive->TankDrive(0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd),
								0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd));
	else
		Robot::drive->TankDrive(0.15, 0.15, true);

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveDistance::IsFinished() {
	double avgEncTick = (Robot::drive->GetLEncoder() + Robot::drive->GetREncoder()) / 2.0;
	double error = desiredEncTick - avgEncTick;
	return error < 50;
}

// Called once after isFinished returns true
void AutoDriveDistance::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveDistance::Interrupted() {

}
