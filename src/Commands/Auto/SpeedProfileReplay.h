#ifndef FULL_PROFILE_REPLAY_H
#define FULL_PROFILE_REPLAY_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class SpeedProfileReplay: public CommandBase {
public:
	SpeedProfileReplay(std::string replayName, bool smartdash);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	std::string rName;
	bool loadSD;
};

#endif  // EXAMPLE_COMMAND_H
