#ifndef AUTO_DRIVE_TURN_H
#define AUTO_DRIVE_TURN_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class AutoDriveTurn: public CommandBase {
public:
	AutoDriveTurn(double angle);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double maxSpeed = 90;
	double minSpeed = 60;
	double slowStart = 15;
	double slowEnd = 9;
	double desiredAngle;
};

#endif  // EXAMPLE_COMMAND_H
