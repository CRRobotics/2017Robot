#include <CustomControlLoop.h>
#include "JoystickCurveDrive.h"
#define kCurveEffect 0.125

JoystickCurveDrive::JoystickCurveDrive()
{
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void JoystickCurveDrive::Initialize()
{
	if (Robot::drive->BothEncodersPresent())
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		Robot::drive->SetDriveRampRate(1.4);
	}
	else
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
}

// Called repeatedly when this Command is scheduled to run
void JoystickCurveDrive::Execute()
{
	bool encodersPresent = Robot::drive->BothEncodersPresent();
	if (!encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::VelocityDriving)
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
	}
	double lSpeed = 0;
	double rSpeed = 0;
	double turnAmount = 0;

	if (fabs(Robot::oi->GetYDriverL()) > 0.05)
		lSpeed = Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL());
	if (fabs(Robot::oi->GetYDriverR()) > 0.05)
		rSpeed = Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR());

	if (fabs(Robot::oi->GetYDriverL()) > 0.1)
		turnAmount += Robot::oi->GetXDriverL() * kCurveEffect ;
	if (fabs(Robot::oi->GetYDriverR()) > 0.1)
		turnAmount += Robot::oi->GetXDriverR() * kCurveEffect;
	Robot::drive->TankDrive(lSpeed + turnAmount, rSpeed - turnAmount, encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::VelocityDriving);
}

// Make this return true when this Command no longer needs to run execute()
bool JoystickCurveDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void JoystickCurveDrive::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JoystickCurveDrive::Interrupted()
{

}
