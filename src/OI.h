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
#define TOGGLE_SHOOTER 8 //
#define STORAGE_FEED_SHOOTER 9
#define EXTEND_GEAR 6
#define RETRACT_GEAR 7
#define ACQ_IN 10
#define DRIVE_TO_BOILER 8
#define DRIVE_TO_GEAR 9
#define SHOOTER_ANGLE_FAR 6
#define SHOOTER_ANGLE_SHORT 7
#define TOGGLE_VISION_SHOOTER 2

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
private:
	static bool controllerLeft;
	std::shared_ptr<Joystick> rJoystick1;
	std::shared_ptr<Joystick> rJoystick2;
	std::shared_ptr<Joystick> lJoystick1;
	std::shared_ptr<Joystick> lJoystick2;

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
	std::shared_ptr<JoystickButton> turnToBoiler;
	std::shared_ptr<JoystickButton> turnToGear;
	std::shared_ptr<JoystickButton> shooterAngleFar;
	std::shared_ptr<JoystickButton> shooterAngleShort;

};

#endif  // OI_H
