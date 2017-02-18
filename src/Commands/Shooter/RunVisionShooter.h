#ifndef RUN_VISION_SHOOTER_H
#define RUN_VISION_SHOOTER_H


#include "../../CommandBase.h"
#include "../../Robot.h"
class RunVisionShooter: public Command {
public:
	RunVisionShooter();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	static double GetDesiredSpeed();
	static bool running;
	static double lastDistance;
private:


};

#endif  // EXAMPLE_COMMAND_H
