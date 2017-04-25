#include <Commands/Auto/VisionGearPlacement/VisionGearPlacement.h>
#define ROBOT_WIDTH 16
#define WHEEL_DIAM 4

VisionGearPlacement::VisionGearPlacement()
{
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void VisionGearPlacement::Initialize()
{
	targetAngle = SmartDashboard::GetNumber("target_gear_angle", 0.0);
	double targetDist  = SmartDashboard::GetNumber("target_gear_dist", 0.0);
	double circleRadius = targetDist / (2 * cos(fabs(targetAngle)));
	vRatio =  (circleRadius - ROBOT_WIDTH / 2) - (circleRadius + ROBOT_WIDTH / 2);
	mode = 0;
	arcLength = (180 - 2 * targetAngle) * 180 / 3.1415926535 * (circleRadius + ROBOT_WIDTH / 2);
	targetAngle += Robot::drive->GetYaw();
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityTurning);
}

// Called repeatedly when this Command is scheduled to run
void VisionGearPlacement::Execute()
{
	if (mode == 0)
	{
		double error = targetAngle - Robot::drive->GetYaw();
		double dir = 1;
		if (error < 0)
			dir = -1;
		error = fabs(error);
		if (error > 7)//Assume max of 40 degrees in this context
			Robot::drive->TankDrive(dir * (17 + (error - 7) / 20 * 15), -1 * dir * (17 + (error - 7) / 20 * 15), false);
		else
			Robot::drive->TankDrive(17 * dir, -17 * dir, false);

		if (error < 1)
		{
			RobotMap::driverDrive1->ClearIaccum();
			RobotMap::drivelDrive1->ClearIaccum();
			Robot::drive->TankDrive(0.0,0.0,false);
			mode = 1;
		}
	}
	else if (mode == 1)
	{
		RobotMap::driverDrive1->SetPID(1.2,0.009,2.6,0.135);
		RobotMap::drivelDrive1->SetPID(1.2,0.009,2.6,0.135);
		double currentTime = DriverStation::GetInstance().GetMatchTime();
		if (lastTime != 0)//Integrate our distTravelled
		{
			double timeElapsed = lastTime - currentTime;
			currentDist += Robot::drive->GetRSpeed() * (2 * 3.1415926535 * WHEEL_DIAM) / 60.0 * timeElapsed;
		}
		lastTime = currentTime;
		double error = arcLength - currentDist;
		//if (error > 20)
			Robot::drive->TankDrive(10 * vRatio, 10, false);
		//else
		//	Robot::drive->TankDrive((0.125 + error / 20 * 0.3), (0.125 + error / 20 * 0.3) * vRatio, true);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool VisionGearPlacement::IsFinished()
{
	return mode == 2 || fabs(Robot::oi->GetYDriverL()) > 0.2 || fabs(Robot::oi->GetYDriverR()) > 0.2;
}

// Called once after isFinished returns true
void VisionGearPlacement::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void VisionGearPlacement::Interrupted()
{

}
