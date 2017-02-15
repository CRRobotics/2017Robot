#ifndef START_CLIMBER_H
#define START_CLIMBER_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class StartClimber: public CommandBase {
public:
	StartClimber();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
