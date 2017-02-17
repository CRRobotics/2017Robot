#ifndef SHIFT_HIGH_H
#define SHIFT_HIGH_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class ShiftHigh: public CommandBase {
public:
	ShiftHigh();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
