#ifndef RUN_SHOOTER_H
#define RUN_SHOOTER_H


#include "../../CommandBase.h"
#include "../../Robot.h"
class RunShooter: public Command {
public:
	RunShooter();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	static double GetDesiredSpeed();
};

#endif  // EXAMPLE_COMMAND_H
