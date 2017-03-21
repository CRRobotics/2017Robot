/*
 * GearTopPeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearTopPeg.h"
#include "../Drive/AutoDriveDistance.h"
#include "../Drive/AutoDriveTurn.h"
#include "../Drive/MoveGearOntoLift.h"

GearTopPeg::GearTopPeg()
{
	AddSequential(new AutoDriveDistance(-70.75));
	if (DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed)
		AddSequential(new AutoDriveTurn(-60));
	else
		AddSequential(new AutoDriveTurn(60));
	AddSequential(new AutoDriveDistance(-73.5));
	AddSequential(new MoveGearOntoLift(), 5);
}

