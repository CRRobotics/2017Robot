// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "CANTalon.h"

#include "Robot.h"
#include "Drive.h"
#include "../RobotMap.h"
#include "Commands/Drive/JoystickDrive.h"
#include "Commands/Drive/JoystickCurveDrive.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

double Drive::maxSpeed = 600.0;//800.0;

Drive::Drive() : Subsystem("Drive")
{
    rDrive1 = RobotMap::driverDrive1;
    rDrive2 = RobotMap::driverDrive2;
    lDrive1 = RobotMap::drivelDrive1;
    lDrive2 = RobotMap::drivelDrive2;
    gearShift = RobotMap::drivegearShift;
    ahrs = RobotMap::driveahrs;

    rDrive1->SetAllowableClosedLoopErr(0);
    lDrive1->SetAllowableClosedLoopErr(0);

    currentControlMode = DriveControlMode::Voltage;
    closedLoopRampRate = 12.6;
}

void Drive::InitDefaultCommand()
{
	SetDefaultCommand(new JoystickDrive());
}

Drive::DriveControlMode Drive::GetControlMode()
{
	return currentControlMode;
}

void Drive::SetDriveRampRate(double rampRate)
{
	rDrive1->SetCloseLoopRampRate(rampRate);
	lDrive1->SetCloseLoopRampRate(rampRate);
	closedLoopRampRate = rampRate;
}

double Drive::GetDriveRampRate()
{
	return closedLoopRampRate;
}

int Drive::GetLEncoderRate()
{
	return lDrive1->GetEncVel();
}

double Drive::GetLSpeed()
{
	return lDrive1->GetSpeed();
}

double Drive::GetRSpeed()
{
	return rDrive1->GetSpeed();
}

int Drive::GetREncoderRate()
{
	return rDrive1->GetEncVel();
}

// Takes input from -1 to 1
void Drive::TankDrive(double lSpeed, double rSpeed, bool speedClosed)
{
	if (!speedClosed)
{
		rDrive1->Set(-rSpeed);
		lDrive1->Set(lSpeed);
	}
	else{
		rDrive1->Set(-rSpeed * maxSpeed);
		lDrive1->Set(lSpeed * maxSpeed);
	}
}

void Drive::ChangeGear(bool high)
{
	gearShift->Set(!high);
}


int Drive::GetLEncoder()
{
	return lDrive1->GetEncPosition();
}

int Drive::GetREncoder()
{
	return rDrive1->GetEncPosition();
}

double Drive::GetLPosition()
{
	return lDrive1->GetPosition();
}

double Drive::GetRPosition()
{
	return rDrive1->GetPosition();
}

double Drive::GetYaw()
{
	return ahrs->GetYaw();
}

void Drive::ResetYaw()
{
	ahrs->ZeroYaw();
	ahrs->ResetDisplacement();
}

bool Drive::GetGear()
{
	return gearShift->Get();
}

//Should be run once every time we change into a control mode
void Drive::SetControlMode(DriveControlMode cMode)
{
	switch (cMode)
	{
		case DriveControlMode::MotionProfile:
			rDrive1->SetControlMode(CANTalon::ControlMode::kMotionProfile);
			lDrive1->SetControlMode(CANTalon::ControlMode::kMotionProfile);
			if (Robot::tMode == Robot::TestMode::DRIVE_MOTION_PROFILE)
			{
				motionP = frc::SmartDashboard::GetNumber("test_pCons", 0.0);
				motionI = frc::SmartDashboard::GetNumber("test_iCons", 0.0);
				motionD = frc::SmartDashboard::GetNumber("test_dCons", 0.0);
				motionF = frc::SmartDashboard::GetNumber("test_fCons", 0.0);
			}
			rDrive1->SetPID(motionP, motionI, motionD, motionF);
			lDrive1->SetPID(motionP, motionI, motionD, motionF);
		break;
		case DriveControlMode::VelocityDriving:
			rDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
			lDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
			if (Robot::tMode == Robot::TestMode::DRIVE_SPEED)
			{
				vDriveP = frc::SmartDashboard::GetNumber("test_pCons", 0.0);
				vDriveI = frc::SmartDashboard::GetNumber("test_iCons", 0.0);
				vDriveD = frc::SmartDashboard::GetNumber("test_dCons", 0.0);
				vDriveF = frc::SmartDashboard::GetNumber("test_fCons", 0.0);
			}
			rDrive1->SetPID(vDriveP, vDriveI, vDriveD, vDriveF);
			lDrive1->SetPID(vDriveP, vDriveI, vDriveD, vDriveF);
		break;
		case DriveControlMode::VelocityTurning:
			rDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
			lDrive1->SetControlMode(CANTalon::ControlMode::kSpeed);
			if (Robot::tMode == Robot::TestMode::DRIVE_TURN_SPEED)
			{
				vTurnP = frc::SmartDashboard::GetNumber("test_pCons", 0.0);
				vTurnI = frc::SmartDashboard::GetNumber("test_iCons", 0.0);
				vTurnD = frc::SmartDashboard::GetNumber("test_dCons", 0.0);
				vTurnF = frc::SmartDashboard::GetNumber("test_fCons", 0.0);
			}
			rDrive1->SetPID(vTurnP, vTurnI, vTurnD, vTurnF);
			lDrive1->SetPID(vTurnP, vTurnI, vTurnD, vTurnF);
		break;
		case DriveControlMode::Voltage:
			rDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
			lDrive1->SetControlMode(CANTalon::ControlMode::kPercentVbus);
		break;
	};
	currentControlMode = cMode;
}

void Drive::SetPIDF(double kp, double ki, double kd, double kf)
{
	rDrive1->SetPID(kp, ki, kd, kf);
	lDrive1->SetPID(kp, ki, kd, kf);
}

bool Drive::BothEncodersPresent()
{
	CANTalon::FeedbackDeviceStatus lStatus = lDrive1->IsSensorPresent(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	CANTalon::FeedbackDeviceStatus rStatus = rDrive1->IsSensorPresent(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	if (lStatus == CANTalon::FeedbackDeviceStatus::FeedbackStatusPresent && rStatus == CANTalon::FeedbackDeviceStatus::FeedbackStatusPresent)
		return true;
	else
	{
		DriverStation::ReportError("ERROR: Encoders not found");
		return false;
	}
}

bool Drive::NavXPresent()
{
	return ahrs->IsConnected();
}
