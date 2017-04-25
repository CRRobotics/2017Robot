/*
 * PegTest.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include <Commands/KitbotTesting/PegTest.h>
#include "../Auto/SpeedProfileReplay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"
#include "../Shooter/RunShooter.h"
#include "../Shooter/FireBalls.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Auto/Delay.h"

PegTest::PegTest()
{
	AddSequential(new SpeedProfileReplay("kitbot_test1.csv", false), 4.6);
	AddSequential(new DriveForwardAtSpeed(0.0), 1.0);
	AddSequential(new SpeedProfileReplay("kitbot_test3.csv", false), 7.7);
}

