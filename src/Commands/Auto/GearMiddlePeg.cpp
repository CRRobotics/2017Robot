/*
 * GearMiddlePeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearMiddlePeg.h"
#include "../Drive/VoltageSpeedDrive.h"
#include "../Drive/MoveGearOntoLift.h"

GearMiddlePeg::GearMiddlePeg() {
	AddSequential(new VoltageSpeedDrive(-7), 4);
	AddSequential(new MoveGearOntoLift(), 5);
}

