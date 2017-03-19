#include <CustomControlLoop.h>
#include "SmoothJoystickDrive.h"

double SmoothJoystickDrive::acc_limit = 2000 * 0.05;

SmoothJoystickDrive::SmoothJoystickDrive() {
	Requires(Robot::drive.get());
}

void SmoothJoystickDrive::Initialize() {
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

void SmoothJoystickDrive::Execute() {
	double joystickL = Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL()) * Drive::maxEncVel;
	double joystickR = Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR()) * Drive::maxEncVel;
	double currentL = Robot::drive->GetLEncoderRate();
	double currentR = Robot::drive->GetREncoderRate();
	double dL = joystickL - currentL;
	double dR = joystickR - currentR;
	if (fabs(dL) > acc_limit)
		dL = dL / fabs(dL) * acc_limit;
	if (fabs(dR) > acc_limit)
		dR = dR / fabs(dR) * acc_limit;
	Robot::drive->TankDrive(currentL + dL, currentR + dR, false);
}

bool SmoothJoystickDrive::IsFinished() {
	return false;
}

void SmoothJoystickDrive::End() {

}

void SmoothJoystickDrive::Interrupted() {

}
