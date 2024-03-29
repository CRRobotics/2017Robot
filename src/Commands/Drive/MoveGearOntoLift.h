#ifndef GEAR_TO_LIFT_H
#define GEAR_TO_LIFT_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class MoveGearOntoLift: public CommandBase {
public:
	MoveGearOntoLift();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	int ticker;
};

#endif  // EXAMPLE_COMMAND_H
