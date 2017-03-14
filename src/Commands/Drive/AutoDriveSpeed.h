#ifndef AUTO_DRIVE_SPEED_H
#define AUTO_DRIVE_SPEED_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class AutoDriveSpeed: public CommandBase {
public:
	AutoDriveSpeed();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double speed;
};

#endif  // EXAMPLE_COMMAND_H
