#include "OI.h"

#include <WPILib.h>
#include "Robot.h"

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
	driveShiftHighGear.reset(new JoystickButton(driverR.get(), SHIFT_HIGH_GEAR));
	drivePTO.reset(new JoystickButton(controllerR.get(), SHIFT_PTO));
	toggleShooter.reset(new JoystickButton(controllerL.get(), TOGGLE_SHOOTER));
	storageFeedShooter.reset(new JoystickButton(controllerL.get(), STORAGE_FEED_SHOOTER));
	extendGear.reset(new JoystickButton(controllerL.get(), EXTEND_GEAR));
	retractGear.reset(new JoystickButton(controllerL.get(), RETRACT_GEAR));
	acqIn.reset(new JoystickButton(controllerL.get(), ACQ_IN));
	turnToBoiler.reset(new JoystickButton(driverR.get(), DRIVE_TO_BOILER));
	turnToGear.reset(new JoystickButton(driverR.get(), DRIVE_TO_GEAR));
	shooterAngleFar.reset(new JoystickButton(driverR.get(), SHOOTER_ANGLE_FAR));
	shooterAngleShort.reset(new JoystickButton(driverR.get(), SHOOTER_ANGLE_SHORT));
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
