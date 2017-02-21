/*
 * FireBallsLow.h
 *
 *  Created on: Feb 19, 2017
 *      Author: adnew
 */

#ifndef SRC_COMMANDS_SHOOTER_FIREBALLSLOW_H_
#define SRC_COMMANDS_SHOOTER_FIREBALLSLOW_H_

#include "../../CommandBase.h"
#include "../../Robot.h"
class FireBallsLow: public Command {
public:
	FireBallsLow();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif /* SRC_COMMANDS_SHOOTER_FIREBALLS_H_ */
