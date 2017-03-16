#ifndef SMOOTH_JOYSTICK_DRIVE_H
#define SMOOTH_JOYSTICK_DRIVE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class SmoothJoystickDrive: public CommandBase {
public:
	SmoothJoystickDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	static double acc_limit;
};

#endif  // EXAMPLE_COMMAND_H
