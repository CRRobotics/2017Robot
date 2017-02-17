#ifndef AUTO_DRIVE_DISTANCE_H
#define AUTO_DRIVE_DISTANCE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class AutoDriveDistance: public CommandBase {
public:
	AutoDriveDistance(double dist);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double maxSpeed;//Percentage from 0 to 1
	double slowStart;
	double slowEnd;
	double desiredEncTick;
	double desiredDist;
};

#endif  // EXAMPLE_COMMAND_H
