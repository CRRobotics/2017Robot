/*
 * HopperAndShoot.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "HopperAndShoot.h"
#include "SpeedProfileReplay.h"
#include "../Acquisition/ToggleHopper.h"
#include "../Storage/FeedFuel.h"
#include "../Shooter/RunShooter.h"
#include "../Shooter/FireBalls.h"
#include "../Drive/AutoDriveTurn.h"
#include "Delay.h"

HopperAndShoot::HopperAndShoot()
{
	AddParallel(new SpeedProfileReplay("hit_hopper.csv", false), 4);
	AddSequential(new Delay(), 2);
	AddParallel(new RunShooter(3100));
	AddSequential(new ToggleHopper(), 0.25);
	AddSequential(new Delay(), 1);
	AddSequential(new FeedFuel(), 3.0);
	AddParallel(new SpeedProfileReplay("hopper_to_shoot.csv", false), 3);
	AddSequential(new Delay(), 2.7);
	AddSequential(new FireBalls(false, 3000));
}

