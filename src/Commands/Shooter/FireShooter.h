#ifndef FIRE_SHOOTER_H
#define FIRE_SHOOTER_H


#include "../../CommandBase.h"
#include "../../Robot.h"
class FireShooter: public CommandBase {
public:
	FireShooter();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	static double GetDesiredSpeed();
};

#endif  // EXAMPLE_COMMAND_H
