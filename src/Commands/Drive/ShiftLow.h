#ifndef SHIFT_LOW_H
#define SHIFT_LOW_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class ShiftLow: public CommandBase {
public:
	ShiftLow();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
