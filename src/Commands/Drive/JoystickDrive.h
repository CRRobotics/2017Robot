#ifndef JOYSTICK_DRIVE_H
#define JOYSTICK_DRIVE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class JoystickDrive: public CommandBase {
public:
	JoystickDrive();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
