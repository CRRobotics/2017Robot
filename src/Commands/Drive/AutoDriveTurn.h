#ifndef AUTO_DRIVE_TURN_H
#define AUTO_DRIVE_TURN_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class AutoDriveTurn: public CommandBase {
public:
	AutoDriveTurn();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
