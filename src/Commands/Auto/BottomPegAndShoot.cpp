/*
 * BottomPegAndShoot.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "BottomPegAndShoot.h"
#include "SpeedProfileReplay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"
#include "../Shooter/RunShooter.h"
#include "../Shooter/FireBalls.h"
#include "../Drive/AutoDriveTurn.h"
#include "Delay.h"

BottomPegAndShoot::BottomPegAndShoot()
{
	AddSequential(new SpeedProfileReplay("gear_bot.csv", false), 8);
	AddParallel(new GearOut(), 0.25);
	AddParallel(new RunShooter());
	AddSequential(new Delay(), 0.5);
	AddSequential(new SpeedProfileReplay("gear_bot_to_key.csv", false));
	AddSequential(new AutoDriveTurn(-129.42));
	AddSequential(new FireBalls(false, 3100));
}

