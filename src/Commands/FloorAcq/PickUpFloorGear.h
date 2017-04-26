#ifndef PICK_UP_FLOOR_GEAR_H
#define PICK_UP_FLOOR_GEAR_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class PickUpFloorGear: public CommandBase {
public:
	PickUpFloorGear();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
private:
	int drop_ticker;
	int mode;
	bool firstTime;
};

#endif  // EXAMPLE_COMMAND_H
