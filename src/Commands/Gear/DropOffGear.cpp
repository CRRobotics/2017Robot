/*
 * DropOffGear.cpp
 *
 *  Created on: Mar 21, 2017
 *      Author: Driver
 */

#include <Commands/Gear/DropOffGear.h>
#include "GearIn.h"
#include "GearOut.h"

DropOffGear::DropOffGear()
{
	AddSequential(new GearOut(), 1.25);
	AddSequential(new GearIn());
}

