#ifndef RUN_SHOOTER_H
#define RUN_SHOOTER_H


#include "../../CommandBase.h"
#include "../../Robot.h"
class RunShooter: public Command {
public:
	RunShooter();
	RunShooter(double withSpeed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double GetDesiredSpeed();
private:
	double desiredSpeed;
};

#endif  // EXAMPLE_COMMAND_H
