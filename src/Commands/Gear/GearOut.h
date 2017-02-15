#ifndef GEAR_OUT_H
#define GEAR_OUT_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class GearOut: public CommandBase {
public:
	GearOut();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
