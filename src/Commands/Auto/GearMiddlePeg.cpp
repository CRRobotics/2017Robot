/*
 * GearMiddlePeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearMiddlePeg.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Drive/MoveGearOntoLift.h"

GearMiddlePeg::GearMiddlePeg()
{
	AddSequential(new DriveForwardAtSpeed(280), 2.8);
	//AddSequential(new MoveGearOntoLift(), 2);
}

