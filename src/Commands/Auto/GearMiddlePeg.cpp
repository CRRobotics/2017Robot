/*
 * GearMiddlePeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearMiddlePeg.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "SpeedProfileReplay.h"
#include "../Drive/MoveGearOntoLift.h"
#include "../Gear/GearIn.h"
#include "../Gear/GearOut.h"

GearMiddlePeg::GearMiddlePeg()
{
	//AddSequential(new DriveForwardAtSpeed(280), 1.9);
	//AddSequential(new GearOut(), 0.25);
	AddSequential(new SpeedProfileReplay("gear_middle.csv", false), 6.0);
	AddSequential(new GearOut(), 0.4);
	AddSequential(new DriveForwardAtSpeed(-200), 3);
	AddSequential(new GearIn());
	//AddSequential(new MoveGearOntoLift(), 2);
}

