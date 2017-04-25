#ifndef POS_TRACKER_H
#define POS_TRACKER_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class PositionTracker: public CommandBase {
public:
	PositionTracker();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double xPos;
	double yPos;
	long lastTime;
};

#endif  // EXAMPLE_COMMAND_H
