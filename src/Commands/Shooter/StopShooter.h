#ifndef STOP_SHOOTER_H
#define STOP_SHOOTER_H


#include "../../CommandBase.h"
#include "../../Robot.h"
class StopShooter: public Command {
public:
	StopShooter();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
