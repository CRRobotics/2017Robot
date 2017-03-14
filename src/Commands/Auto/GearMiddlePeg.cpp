/*
 * GearMiddlePeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearMiddlePeg.h"
#include "../Drive/AutoDriveDistance.h"
#include "../Drive/MoveGearOntoLift.h"

GearMiddlePeg::GearMiddlePeg() {
	AddSequential(new AutoDriveDistance(-82));
	AddSequential(new MoveGearOntoLift(), 5);
}

