#include <Commands/Auto/StereoscopicTurn.h>
#include "../../AngleMethods.h"
#define CAMERA_R 10

StereoscopicTurn::StereoscopicTurn(double angle)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
	desiredAngle = angle;
	xAngle1 = 0;
	xAngle2 = 0;
	yaw1 = 0;
	yaw2 = 0;
	accurateXAngle1 = 0;
	distance = 0;
	lastTicker = 0;
}

// Called just before this Command runs the first time
void StereoscopicTurn::Initialize()
{
//	if (Robot::tMode == Robot::TestMode::DRIVE_TURN_SPEED)
//	{
//		desiredAngle = SmartDashboard::GetNumber("test_setPoint", 0);
//		maxSpeed = SmartDashboard::GetNumber("test_max_speed", 0);
//		slowStart = SmartDashboard::GetNumber("test_slow_start", 0);
//		slowEnd = SmartDashboard::GetNumber("test_slow_end", 0);
//	}
//	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityTurning);

	if (Robot::drive->BothEncodersPresent())
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
	internalTicker = 0;
	xAngle1 = 0;
	xAngle2 = 0;
	if (Robot::table != nullptr)
		lastTicker = Robot::table->GetNumber("ticker", 0);
}

// Called repeatedly when this Command is scheduled to run
void StereoscopicTurn::Execute()
{
	if (Robot::table != nullptr && Robot::drive->BothEncodersPresent())
	{
		if (stage == 0) // grab first frame
		{
			if (Robot::table->GetNumber("ticker", -1) != lastTicker)
			{
				xAngle1 = Robot::table->GetNumber("XAngleToTarget", 0);
				lastTicker = Robot::table->GetNumber("ticker", -1);
				yaw1 = Robot::drive->GetYaw();
				stage++;
			}
		}
		else if (stage == 1)
		{
			if (xAngle1 > 0)
			{
				Robot::drive->TankDrive(-100, 100);
				if (internalTicker > 20)
					stage++;
			}
			else
			{
				Robot::drive->TankDrive(100, -100);
				if (internalTicker > 20)
					stage++;
			}
			internalTicker++;
		}
		else if (stage == 2) //grab second frame
		{
			Robot::drive->TankDrive(0, 0);
			if (Robot::table->GetNumber("ticker", 0) != lastTicker)
			{
				xAngle2 = SmartDashboard::GetNumber("XAngleToTarget", 0);
				yaw2 = Robot::drive->GetYaw();
				double dYaw = angle_diff(Robot::drive->GetYaw(), yaw2);
				lastTicker = Robot::table->GetNumber("ticker", 0);
				stage++;
				//Perform spectroscopic analysis
				double y1 = tan((dYaw + xAngle2) * 180 / 3.14159265) * (CAMERA_R - CAMERA_R * cos(dYaw * 180 / 3.14159265)) + CAMERA_R * sin (dYaw * 180 / 3.14159265);
				y1 = y1 / (tan(xAngle1) - tan((dYaw + xAngle2) * 180 / 3.14159265));
				double x1 = y1 * tan(xAngle1);
				y1 += CAMERA_R;
				distance = sqrt(x1 * x1 + y1 * y1);
				accurateXAngle1 = atan2(x1, y1);
				accurateXAngle1 -= dYaw;
				accurateXAngle1 += Robot::drive->GetYaw();
				accurateXAngle1 = formatAngle(accurateXAngle1);
				stage++;
			}
		}
		else
		{

		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StereoscopicTurn::IsFinished()
{
	double currentAngle = Robot::drive->GetYaw();
	double error = angle_diff(desiredAngle, currentAngle);
	if (!Robot::drive->BothEncodersPresent())
		return true;
	return fabs(error) < 1;
}

// Called once after isFinished returns true
void StereoscopicTurn::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StereoscopicTurn::Interrupted()
{

}
