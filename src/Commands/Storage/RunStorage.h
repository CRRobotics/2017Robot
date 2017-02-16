#ifndef RUN_STORAGE_H
#define RUN_STORAGE_H

#include "../../CommandBase.h"
#include "../Shooter/FireShooter.h"

class RunStorage: public CommandBase {
public:
	RunStorage();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
