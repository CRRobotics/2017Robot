#ifndef STEREOSCOPIC_TURN_H
#define STEREOSCOPIC_TURN_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class StereoscopicTurn: public CommandBase {
public:
	StereoscopicTurn(double angle);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double maxSpeed;//0 to 1
	double slowStart;
	double slowEnd;
	double desiredAngle;
};

#endif  // EXAMPLE_COMMAND_H
