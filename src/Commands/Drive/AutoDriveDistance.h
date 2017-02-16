#ifndef AUTO_DRIVE_DISTANCE_H
#define AUTO_DRIVE_DISTANCE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class AutoDriveDistance: public CommandBase {
public:
	AutoDriveDistance();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
