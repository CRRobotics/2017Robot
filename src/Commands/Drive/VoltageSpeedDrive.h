#ifndef VOLTAGE_SPEED_DRIVE_H
#define VOLTAGE_SPEED_DRIVE_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class VoltageSpeedDrive: public CommandBase {
public:
	VoltageSpeedDrive(double v);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double voltage;
};

#endif  // EXAMPLE_COMMAND_H
