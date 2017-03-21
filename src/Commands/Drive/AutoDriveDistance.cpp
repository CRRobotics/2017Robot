#include "AutoDriveDistance.h"
#include "Robot.h"

AutoDriveDistance::AutoDriveDistance(double dist)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	desiredDist = dist;
	startAngle = 0;
	slowEnd = 400;
	slowStart = 1600;
	maxSpeed = 0.8;
	desiredR = 0;
}

// Called just before this Command runs the first time
void AutoDriveDistance::Initialize()
{
	if (Robot::tMode == Robot::TestMode::DRIVE_POSITION)
	{
		desiredDist = SmartDashboard::GetNumber("test_setPoint", 0);
		maxSpeed = SmartDashboard::GetNumber("test_max_speed", 0);
		slowStart = SmartDashboard::GetNumber("test_slow_start", 0);
		slowEnd = SmartDashboard::GetNumber("test_slow_end", 0);
	}
	double avgR = (Robot::drive->GetLPosition() + Robot::drive->GetRPosition()) / 2.0;
	desiredR = avgR + desiredDist * R_PER_IN;
	if (Robot::drive->BothEncodersPresent())
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	startAngle = Robot::drive->GetYaw();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveDistance::Execute()
{
	double avgR = (Robot::drive->GetLPosition() + Robot::drive->GetRPosition()) / 2.0;
	double error = desiredR - avgR;
	int sign = 1;
	if (error < 0)
		sign = -1;
	error = fabs(error);
	double angleError = startAngle - Robot::drive->GetYaw();
	double aCorr = angleError * kTurn;
	if (error > slowStart)
		Robot::drive->TankDrive((maxSpeed) * sign + aCorr, (maxSpeed) * sign - aCorr, true);
	else if (error > slowEnd)
		Robot::drive->TankDrive((0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd)) * sign + aCorr,
								(0.15 + (maxSpeed - 0.15) * (error - slowEnd) / (slowStart - slowEnd)) * sign - aCorr, true);
	else
		Robot::drive->TankDrive((0.15) * sign + aCorr, (0.15) * sign - aCorr, true);

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveDistance::IsFinished()
{
	if (!Robot::drive->BothEncodersPresent())
		return true;
	double avgR = (Robot::drive->GetLPosition() + Robot::drive->GetRPosition()) / 2.0;
	double error = desiredR- avgR;
	return fabs(error) < 0.5;
}

// Called once after isFinished returns true
void AutoDriveDistance::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveDistance::Interrupted()
{

}
