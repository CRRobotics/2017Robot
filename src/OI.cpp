#include "OI.h"

#include <WPILib.h>

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
	//frc::Joystick controllerL = new frc::Joystick();
	//Joystick controllerR = new Joystick();
	//Joystick driverL = new Joystick();
	//Joystick driverR = new Joystick();
	if (controllerLeft){
		/*controllerL = lJoystick1.get();
		controllerR = lJoystick2.get();
		driverL = rJoystick1.get();
		driverR = rJoystick2.get();*/
	}
	else{
		/*controllerL = rJoystick1.get();
		controllerR = rJoystick2.get();
		driverL = lJoystick1.get();
		driverR = lJoystick2.get();*/
	}


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
