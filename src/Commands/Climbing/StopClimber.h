#ifndef STOP_CLIMBER_H
#define STOP_CLIMBER_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class StopClimber: public CommandBase {
public:
	StopClimber();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
