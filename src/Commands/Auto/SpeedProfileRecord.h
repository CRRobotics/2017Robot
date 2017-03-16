#ifndef FULL_PROFILE_Record_H
#define FULL_PROFILE_Record_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class SpeedProfileRecord: public CommandBase {
public:
	SpeedProfileRecord();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
