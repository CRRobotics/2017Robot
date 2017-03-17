#ifndef VOLT_PROFILE_REPLAY_H
#define VOLT_PROFILE_REPLAY_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class VoltProfileReplay: public CommandBase {
public:
	VoltProfileReplay(std::string replayName);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	std::string rName;
};

#endif  // EXAMPLE_COMMAND_H
