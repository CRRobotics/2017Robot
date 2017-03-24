/*
 * GearBottomPeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearBottomPeg.h"
#include "../Drive/AutoDriveDistance.h"
#include "../Drive/AutoDriveTurn.h"
#include "../Drive/MoveGearOntoLift.h"

GearBottomPeg::GearBottomPeg()
{
	//AddSequential (new SpeedProfileReplay("gear_bot.csv",false), 8);
	//AddSequential (new GearOut());
	//AddSequential (new DriveForwardAtSpeed(0), 1);
	//AddSequential (new DriveForwardAtSpeed(-50), 3);
	//AddSequential(new AutoDriveDistance(-70.75));
	//if (DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed)
	//	AddSequential(new AutoDriveTurn(60));
	//else
	//	AddSequential(new AutoDriveTurn(-60));
	//AddSequential(new AutoDriveDistance(-73.5));
	//AddSequential(new MoveGearOntoLift(), 5);
}

