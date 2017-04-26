#ifndef GEAR_OUT_WITH_SENSOR_H
#define GEAR_OUT_WITH_SENSOR_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class GearOutWithSensor: public CommandBase {
public:
	GearOutWithSensor();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
