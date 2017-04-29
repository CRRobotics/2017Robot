#ifndef OPEN_UP_FLOOR_GEAR_H
#define OPEN_UP_FLOOR_GEAR_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class OpenFloorAcq: public CommandBase {
public:
	OpenFloorAcq();
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
