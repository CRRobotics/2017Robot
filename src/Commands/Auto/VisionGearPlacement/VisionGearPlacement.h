#ifndef VisionGearPlacement_H
#define VisionGearPlacement_H

#include "../../../CommandBase.h"
#include "../../../Robot.h"

class VisionGearPlacement: public CommandBase {
public:
	VisionGearPlacement();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double targetAngle;
	double vRatio;
	double arcLength;
	double currentDist;
	double lastTime;
	int mode;
};

#endif  // EXAMPLE_COMMAND_H
