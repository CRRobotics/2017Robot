/*
 * MiddlePegAndShootRecorded.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "MiddlePegAndShootRecorded.h"
#include "SpeedProfileReplay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"
#include "../Shooter/RunShooter.h";
#include "../Shooter/FireBalls.h"
#include "Delay.h"

MiddlePegAndShootRecorded::MiddlePegAndShootRecorded()
{
	AddParallel(new SpeedProfileReplay("", false));
	AddSequential(new Delay(), 2.5);
	AddSequential(new GearOut());
	AddParallel(new RunShooter());
	AddSequential(new Delay(), 4);
	AddSequential(new FireBalls(false, 3000), 4.0);
}

