#include "AutoDriveTurn.h"
#include "../../AngleMethods.h"

AutoDriveTurn::AutoDriveTurn(double angle) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	desiredAngle = angle;
}

// Called just before this Command runs the first time
void AutoDriveTurn::Initialize() {
	if (Robot::tMode == Robot::TestMode::DRIVE_TURN_SPEED)
	{
		desiredAngle = SmartDashboard::GetNumber("test_setPoint", 0);
		maxSpeed = SmartDashboard::GetNumber("test_max_speed", 0);
		minSpeed = SmartDashboard::GetNumber("test_min_speed", 0);
		slowStart = SmartDashboard::GetNumber("test_slow_start", 0);
		slowEnd = SmartDashboard::GetNumber("test_slow_end", 0);
	}
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveTurn::Execute() {
	double currentAngle = Robot::drive->GetYaw();
	//SmartDashboard::PutNumber("Robot yaw", Robot::drive->GetYaw());
	double error = angle_diff(desiredAngle, currentAngle);
	printf("%f %f\n", currentAngle, desiredAngle);
	SmartDashboard::PutNumber("angle error", error);
	double direction = 1;
	if (error < 0)
		direction = -1;
	error = fabs(error);
	if (error > slowStart)
		Robot::drive->TankDrive(-1 * direction * maxSpeed, direction * maxSpeed, true);
	else if (error > slowEnd)
		Robot::drive->TankDrive(-1 * direction * minSpeed + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd),
								direction * (minSpeed + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd)));
	else
		Robot::drive->TankDrive(-1 * direction * minSpeed, direction * minSpeed, true);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveTurn::IsFinished() {
	double currentAngle = Robot::drive->GetYaw();
	double error = angle_diff(desiredAngle, currentAngle);
	return fabs(error) < 2.5 || fabs(Robot::oi->GetYDriverL()) > 0.2 || fabs(Robot::oi->GetYDriverR()) > 0.2;
}

// Called once after isFinished returns true
void AutoDriveTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveTurn::Interrupted() {

}
