/*
 * GearTopPeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearTopPeg.h"
#include "SpeedProfileReplay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Drive/AutoDriveTurn.h"

GearTopPeg::GearTopPeg()
{
	AddSequential(new SpeedProfileReplay("gear_bot.csv", false));
	AddSequential(new GearOut());
	AddSequential(new DriveForwardAtSpeed(-80), 1.0);
	AddParallel(new GearIn());
	AddSequential(new AutoDriveTurn(-45));
	//AddSequential(new FireBalls(true, 6000));
	/*AddSequential(new AutoDriveDistance(-70.75));
	if (DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed)
		AddSequential(new AutoDriveTurn(-60));
	else
		AddSequential(new AutoDriveTurn(60));
	AddSequential(new AutoDriveDistance(-73.5));
	AddSequential(new MoveGearOntoLift(), 5);*/
}

