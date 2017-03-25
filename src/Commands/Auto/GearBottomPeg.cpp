/*
 * GearBottomPeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearBottomPeg.h"
#include "SpeedProfileReplay.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Drive/AutoDriveTurn.h"
#include "Delay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"

GearBottomPeg::GearBottomPeg()
{
	AddSequential (new SpeedProfileReplay("gear_bot.csv",false), 9.65);
	AddSequential (new GearOut(), 0.25);
	AddSequential (new Delay(), 1);
	AddSequential (new DriveForwardAtSpeed(-50), 3);
	AddSequential (new GearIn());

}

