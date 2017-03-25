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
#include "../Shooter/RunShooter.h"
#include "../Shooter/FireBalls.h"
#include "../Drive/ShiftLow.h"
#include "Delay.h"

MiddlePegAndShootRecorded::MiddlePegAndShootRecorded()
{
	AddSequential(new ShiftLow());
	AddParallel(new SpeedProfileReplay("middle_shoot.csv", false));
	AddSequential(new Delay(), 3.75);
	AddSequential(new GearOut());
	AddParallel(new RunShooter());
	AddSequential(new Delay(), 3);
	AddSequential(new GearIn());
	AddSequential(new Delay(), 1);
	AddSequential(new FireBalls(false, 3000), 4.75);
}

