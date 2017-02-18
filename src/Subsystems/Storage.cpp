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
#include "Storage.h"
#include "../RobotMap.h"



Storage::Storage() : Subsystem("Storage") {
//	std::shared_ptr<Solenoid> Storage::lGatingPiston;
//	std::shared_ptr<Solenoid> Storage::rGatingPiston;
    ballControlMotor = RobotMap::storageballControlMotor;
}

void Storage::InitDefaultCommand() {
}

void Storage::SetControlMode(CANTalon::ControlMode cMode){
	ballControlMotor->SetControlMode(cMode);
	if (cMode == CANTalon::ControlMode::kSpeed)
	{
		ballControlMotor->SetPIDSourceType(PIDSourceType::kRate);
		ballControlMotor->SetPID(storageVP, storageVI, storageVD, storageVF);
	}
	else if(cMode == CANTalon::ControlMode::kPosition)
	{

	}
}

void Storage::MoveStorage(double speed)
{
	ballControlMotor->Set(speed);
}

void Storage::SetGatePosition(bool pos) {
	lGatingPiston->Set(pos);
	rGatingPiston->Set(pos);
}

void Storage::SetLGatePosition(bool pos) {
	lGatingPiston->Set(pos);
}

void Storage::SetRGatePosition(bool pos) {
	rGatingPiston->Set(pos);
}

