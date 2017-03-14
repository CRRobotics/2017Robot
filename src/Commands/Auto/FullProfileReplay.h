#ifndef FULL_PROFILE_REPLAY_H
#define FULL_PROFILE_REPLAY_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class FullProfileReplay: public CommandBase {
public:
	FullProfileReplay();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
