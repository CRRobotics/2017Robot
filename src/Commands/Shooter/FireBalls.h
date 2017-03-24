/*
 * FireBalls.h
 *
 *  Created on: Feb 19, 2017
 *      Author: adnew
 */

#ifndef SRC_COMMANDS_SHOOTER_FIREBALLS_H_
#define SRC_COMMANDS_SHOOTER_FIREBALLS_H_

#include "../../CommandBase.h"
#include "../../Robot.h"
class FireBalls: public Command {
public:
	FireBalls(bool shootHigh, double speed);
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	bool high;
	double GetDesiredSpeed();
	double lastDistance;
	double desiredSpeed;
};


#endif /* SRC_COMMANDS_SHOOTER_FIREBALLS_H_ */
