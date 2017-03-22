#ifndef OI_H
#define OI_H

#define LJOYSTICK_OUTER 0
#define LJOYSTICK_INNER 1
#define RJOYSTICK_OUTER 2
#define RJOYSTICK_INNER 3

#define SHIFT_HIGH_GEAR 11 //driver right
#define SHIFT_LOW_GEAR 6 //driver left
#define SHIFT_PTO_ON 1 //driver right
#define SHIFT_PTO_OFF 1 //driver left
#define DRIVE_TO_BOILER 8 //Driver right
#define DRIVE_TO_GEAR 9 //Driver right
#define DRIVE_TO_LOADING 7//Drive left

//All controller buttons below
#define TOGGLE_SHOOTER 6 //controller left
#define EXTEND_GEAR 9
#define RETRACT_GEAR 8
#define ACQ_IN 11
#define TOGGLE_HOPPER 10
#define EJECT_FUEL 4
#define DROP_GEAR 2
#define SHOOT_FAR 3
#define SHOOT_SHORT 1
#define TOGGLE_VISION_SHOOTER 7

#include "WPILib.h"


class OI {
public:
	OI();
	void SetControllerSide(bool left);
	void MapButtons();
	double GetYControllerL();
	double GetYControllerR();
	double GetYDriverL();
	double GetYDriverR();
	bool GetAcquisition();
	bool GetFiring();
	bool GetDrivePTOOn();
	bool GetDrivePTOOff();
private:
	static bool controllerLeft;
	std::shared_ptr<Joystick> rJoystick1;
	std::shared_ptr<Joystick> rJoystick2;
	std::shared_ptr<Joystick> lJoystick1;
	std::shared_ptr<Joystick> lJoystick2;


	std::shared_ptr<JoystickButton> dropOffGear;
	std::shared_ptr<JoystickButton> ejectFuel;
	std::shared_ptr<JoystickButton> driveLoadingZone;
	std::shared_ptr<JoystickButton> driveShiftHighGear;
	std::shared_ptr<JoystickButton> driveShiftLowGear;
	std::shared_ptr<JoystickButton> drivePTOOn;
	std::shared_ptr<JoystickButton> drivePTOOff;
	std::shared_ptr<JoystickButton> toggleShooter;
	std::shared_ptr<JoystickButton> toggleVisionShooter;
	std::shared_ptr<JoystickButton> storageFeedShooter;
	std::shared_ptr<JoystickButton> extendGear;
	std::shared_ptr<JoystickButton> retractGear;
	std::shared_ptr<JoystickButton> acqIn;
	std::shared_ptr<JoystickButton> runStorage;
	std::shared_ptr<JoystickButton> toggleHopper;
	std::shared_ptr<JoystickButton> turnToBoiler;
	std::shared_ptr<JoystickButton> turnToGear;
	std::shared_ptr<JoystickButton> shooterAngleFar;
	std::shared_ptr<JoystickButton> shooterAngleShort;

};

#endif  // OI_H
