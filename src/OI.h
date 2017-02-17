#ifndef OI_H
#define OI_H

#define LJOYSTICK_OUTER 0
#define LJOYSTICK_INNER 1
#define RJOYSTICK_OUTER 2
#define RJOYSTICK_INNER 3

#define SHIFT_HIGH_GEAR 0
#define SHIFT_LOW_GEAR 0
#define SHIFT_PTO 0
#define TOGGLE_SHOOTER 0
#define STORAGE_FEED_SHOOTER 0
#define EXTEND_GEAR 0
#define RETRACT_GEAR 0
#define ACQ_IN 0
#define DRIVE_TO_BOILER 0
#define DRIVE_TO_GEAR 0
#define SHOOTER_ANGLE_FAR 0
#define SHOOTER_ANGLE_SHORT 0

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
private:
	static bool controllerLeft;
	std::shared_ptr<Joystick> rJoystick1;
	std::shared_ptr<Joystick> rJoystick2;
	std::shared_ptr<Joystick> lJoystick1;
	std::shared_ptr<Joystick> lJoystick2;

	std::shared_ptr<JoystickButton> driveShiftHighGear;
	std::shared_ptr<JoystickButton> driveShiftLowGear;
	std::shared_ptr<JoystickButton> drivePTO;
	std::shared_ptr<JoystickButton> toggleShooter;
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
