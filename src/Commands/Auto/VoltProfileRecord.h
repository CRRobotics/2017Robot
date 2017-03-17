#ifndef VOLT_PROFILE_Record_H
#define VOLT_PROFILE_Record_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class VoltProfileRecord: public CommandBase {
public:
	VoltProfileRecord();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
