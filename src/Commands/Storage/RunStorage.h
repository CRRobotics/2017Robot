#ifndef RUN_STORAGE_H
#define RUN_STORAGE_H

#include <Commands/Shooter/RunShooter.h>
#include "../../CommandBase.h"

class RunStorage: public Command {
public:
	RunStorage();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
