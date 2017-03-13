#include <Commands/Shooter/FireBalls.h>
#include <Commands/Shooter/RunShooter.h>
#include <Commands/Shooter/RunVisionShooter.h>
#include "OI.h"

#include <WPILib.h>
#include "Robot.h"
#include "Commands/Acquisition/AcquisitionIn.h"
#include "Commands/Acquisition/ToggleHopper.h"
#include "Commands/Climbing/StartClimber.h"
#include "Commands/Climbing/StopClimber.h"
#include "Commands/Drive/ShiftHigh.h"
#include "Commands/Drive/ShiftLow.h"
#include "Commands/Gear/GearIn.h"
#include "Commands/Gear/GearOut.h"
#include "Commands/Storage/RunStorage.h"
#include "Commands/Shooter/RunShooter.h"

bool OI::controllerLeft;

OI::OI(){
	rJoystick1.reset(new Joystick(RJOYSTICK_INNER));
	rJoystick2.reset(new Joystick(RJOYSTICK_OUTER));
	lJoystick1.reset(new Joystick(LJOYSTICK_OUTER));
	lJoystick2.reset(new Joystick(LJOYSTICK_INNER));
	controllerLeft = false;
}

void OI::SetControllerSide(bool left){
	controllerLeft = left;
}

void OI::MapButtons(){
	std::shared_ptr<Joystick> controllerL;
	std::shared_ptr<Joystick> controllerR;
	std::shared_ptr<Joystick> driverL;
	std::shared_ptr<Joystick> driverR;
	if (controllerLeft){
		controllerL = lJoystick1;
		controllerR = lJoystick2;
		driverL = rJoystick1;
		driverR = rJoystick2;
	}
	else{
		controllerL = rJoystick1;
		controllerR = rJoystick2;
		driverL = lJoystick1;
		driverR = lJoystick2;
	}
	driveShiftLowGear.reset(new JoystickButton(driverL.get(), SHIFT_LOW_GEAR));
	driveShiftLowGear->WhenPressed(new ShiftLow());

	driveShiftHighGear.reset(new JoystickButton(driverR.get(), SHIFT_HIGH_GEAR));
	driveShiftHighGear->WhenPressed(new ShiftHigh());

	drivePTOOn.reset(new JoystickButton(driverR.get(), SHIFT_PTO_ON));
	drivePTOOn->WhenPressed(new StartClimber());

	drivePTOOff.reset(new JoystickButton(driverL.get(), SHIFT_PTO_OFF));
	drivePTOOff->WhenPressed(new StopClimber());

	toggleShooter.reset(new JoystickButton(controllerL.get(), TOGGLE_SHOOTER));
	toggleShooter->WhenPressed(new RunShooter());

	toggleVisionShooter.reset(new JoystickButton(controllerL.get(), TOGGLE_VISION_SHOOTER));
	toggleVisionShooter->WhenPressed(new RunVisionShooter());

	extendGear.reset(new JoystickButton(controllerL.get(), EXTEND_GEAR));
	extendGear->WhenPressed(new GearOut());

	retractGear.reset(new JoystickButton(controllerL.get(), RETRACT_GEAR));
	retractGear->WhenPressed(new GearIn());

	acqIn.reset(new JoystickButton(controllerL.get(), ACQ_IN));
	//acqIn->WhileHeld(new RunStorage());

	toggleHopper.reset(new JoystickButton(controllerL.get(), TOGGLE_HOPPER));
	toggleHopper->WhenPressed(new ToggleHopper());

	turnToBoiler.reset(new JoystickButton(driverR.get(), DRIVE_TO_BOILER));
	turnToGear.reset(new JoystickButton(driverR.get(), DRIVE_TO_GEAR));

	shooterAngleFar.reset(new JoystickButton(controllerL.get(), SHOOT_FAR));
	shooterAngleFar->WhileHeld(new FireBalls(true));

	shooterAngleShort.reset(new JoystickButton(controllerL.get(), SHOOT_SHORT));
	shooterAngleShort->WhileHeld(new FireBalls(false));
}

double OI::GetYControllerL(){
	if (controllerLeft)
		return lJoystick1->GetY();
	else
		return rJoystick1->GetY();
}

double OI::GetYControllerR(){
	if (controllerLeft)
		return lJoystick2->GetY();
	else
		return rJoystick2->GetY();
}

double OI::GetYDriverL(){
	if (controllerLeft)
		return rJoystick1->GetY();
	else
		return lJoystick1->GetY();
}

double OI::GetYDriverR(){
	if (controllerLeft)
		return rJoystick2->GetY();
	else
		return lJoystick2->GetY();
}

bool OI::GetAcquisition(){
	return acqIn->Get() || toggleHopper->Get();//For testing
}

bool OI::GetDrivePTOOn(){
	return drivePTOOn->Get();
}

bool OI::GetDrivePTOOff(){
	return drivePTOOff->Get();
}
bool OI::GetFiring(){
	return shooterAngleFar->Get() || shooterAngleShort->Get();
}
