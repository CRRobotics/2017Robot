#include <Commands/Auto/StereoscopicTurn.h>
#include "../../AngleMethods.h"

StereoscopicTurn::StereoscopicTurn(double angle) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	desiredAngle = angle;
}

// Called just before this Command runs the first time
void StereoscopicTurn::Initialize() {
	if (Robot::tMode == Robot::TestMode::DRIVE_TURN_SPEED)
	{
		desiredAngle = SmartDashboard::GetNumber("test_setPoint", 0);
		maxSpeed = SmartDashboard::GetNumber("test_max_speed", 0);
		slowStart = SmartDashboard::GetNumber("test_slow_start", 0);
		slowEnd = SmartDashboard::GetNumber("test_slow_end", 0);
	}
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityTurning);
}

// Called repeatedly when this Command is scheduled to run
void StereoscopicTurn::Execute() {
	double currentAngle = Robot::drive->GetYaw();
	double error = angle_diff(desiredAngle, currentAngle);
	double direction = 1;
	if (error < 1)
		direction = -1;
	error = fabs(error);
	if (error > slowStart)
		Robot::drive->TankDrive(maxSpeed, direction * maxSpeed, true);
	else if (error > slowEnd)
		Robot::drive->TankDrive(0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd),
								direction * (0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd)));
	else
		Robot::drive->TankDrive(0.15, direction * 0.15, true);
}

// Make this return true when this Command no longer needs to run execute()
bool StereoscopicTurn::IsFinished() {
	double currentAngle = Robot::drive->GetYaw();
	double error = angle_diff(desiredAngle, currentAngle);
	return fabs(error) < 1;
}

// Called once after isFinished returns true
void StereoscopicTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StereoscopicTurn::Interrupted() {

}
