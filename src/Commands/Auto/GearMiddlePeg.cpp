/*
 * GearMiddlePeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearMiddlePeg.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Drive/MoveGearOntoLift.h"
#include "../Gear/GearIn.h"
#include "../Gear/GearOut.h"

GearMiddlePeg::GearMiddlePeg()
{
	AddSequential(new DriveForwardAtSpeed(280), 1.9);
	//AddSequential(new GearOut(), 0.25);
	AddSequential(new DriveForwardAtSpeed(-40), 2);
	AddSequential(new GearIn());
	//AddSequential(new MoveGearOntoLift(), 2);
}

