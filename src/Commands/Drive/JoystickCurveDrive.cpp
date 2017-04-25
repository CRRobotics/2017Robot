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
//	if (Robot::drive->BothEncodersPresent())
//	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		Robot::drive->SetDriveRampRate(0.25);
//	}
//	else
//		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
}

// Called repeatedly when this Command is scheduled to run
void JoystickCurveDrive::Execute()
{
//	bool encodersPresent = true;//Robot::drive->BothEncodersPresent();
//	//if (!encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::VelocityDriving)
//	//{
//	//	Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);
//	//}
//	double lSpeed = 0;
//	double rSpeed = 0;
//	double turnAmount = 1;
//	double dirL = 1;
//	double dirR = 1;
//	if (Robot::oi->GetYDriverL() < 0.05)
//		dirL = -1;
//	if (Robot::oi->GetYDriverR() < 0.05)
//		dirR = -1;
//
//
//	if (fabs(Robot::oi->GetYDriverL()) > 0.05)
//		lSpeed = Robot::oi->GetYDriverL() * Robot::oi->GetYDriverL() * dirL;
//	if (fabs(Robot::oi->GetYDriverR()) > 0.05)
//		rSpeed = Robot::oi->GetYDriverR() * Robot::oi->GetYDriverR() * dirR;
//
//	if (fabs(Robot::oi->GetXDriverL()) > 0.2)
//		turnAmount *= (1 + Robot::oi->GetXDriverL() * kCurveEffect * dirL * -1);
//	if (fabs(Robot::oi->GetXDriverR()) > 0.2)
//		turnAmount *= (1 + Robot::oi->GetXDriverR() * kCurveEffect * dirR * -1);
//	printf("%f\n", turnAmount);
//	Robot::drive->TankDrive(lSpeed * turnAmount, rSpeed / turnAmount, encodersPresent && Robot::drive->GetControlMode() == Drive::DriveControlMode::VelocityDriving);

	double speed = Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR());
	double turnAmount = 1 + Robot::oi->GetXDriverR() * -1;
	Robot::drive->TankDrive(speed * turnAmount, speed / turnAmount, true);
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
