/*
 * FireBallsHigh.h
 *
 *  Created on: Feb 19, 2017
 *      Author: adnew
 */

#ifndef SRC_COMMANDS_SHOOTER_FIREBALLSHIGH_H_
#define SRC_COMMANDS_SHOOTER_FIREBALLSHIGH_H_

#include "../../CommandBase.h"
#include "../../Robot.h"
class FireBallsHigh: public Command {
public:
	FireBallsHigh();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};


#endif /* SRC_COMMANDS_SHOOTER_FIREBALLSHIGH_H_ */
