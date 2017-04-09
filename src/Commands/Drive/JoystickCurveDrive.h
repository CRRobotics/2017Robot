#ifndef JOYSTICK_CURVE_DRIVE_H
#define JOYSTICK_CURVE_DRIVE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class JoystickCurveDrive: public CommandBase {
public:
	JoystickCurveDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
