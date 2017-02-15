#ifndef ACQUISITION_IN_H
#define ACQUISITION_IN_H

#include "../../CommandBase.h"

class AcquisitionIn: public CommandBase {
public:
	AcquisitionIn();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // EXAMPLE_COMMAND_H
