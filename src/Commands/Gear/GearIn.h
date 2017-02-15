#ifndef GEAR_IN_H
#define GEAR_IN_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class GearIn: public CommandBase {
public:
	GearIn();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
