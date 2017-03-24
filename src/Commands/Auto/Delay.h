#ifndef Delay_H
#define Delay_H

#include "../../CommandBase.h"
#include "../../Robot.h"

class Delay: public CommandBase {
public:
	Delay();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
