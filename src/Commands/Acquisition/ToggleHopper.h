/*
 * ToggleHopper.h
 *
 *  Created on: Feb 21, 2017
 *      Author: adnew
 */

#ifndef SRC_COMMANDS_ACQUISITION_TOGGLEHOPPER_H_
#define SRC_COMMANDS_ACQUISITION_TOGGLEHOPPER_H_

#include "../../CommandBase.h"
#include "../../Robot.h"

class ToggleHopper: public CommandBase {
public:
	ToggleHopper();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif /* SRC_COMMANDS_ACQUISITION_TOGGLEHOPPER_H_ */
