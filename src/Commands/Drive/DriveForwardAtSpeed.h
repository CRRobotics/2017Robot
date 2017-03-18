#ifndef DRIVE_FORWARD_AT_SPEED_H
#define DRIVE_FORWARD_AT_SPEED_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class DriveForwardAtSpeed: public CommandBase {
public:
	DriveForwardAtSpeed(double s);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double speed;
};

#endif  // EXAMPLE_COMMAND_H
