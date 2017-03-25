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
#include "Delay.h"
#include "../Shooter/RunShooter.h"
#include "../Shooter/FireBalls.h"

GearTopPeg::GearTopPeg()
{
	AddSequential(new SpeedProfileReplay("gear_top.csv", false), 9.65);
	//AddSequential(new GearOut(), 0.5);
	AddSequential(new Delay(),0.5);
	//AddSequential(new DriveForwardAtSpeed(-120), 2.0);
	//AddParallel(new GearIn(), 0.5);
	//AddSequential(new AutoDriveTurn(0), 4.0);
	//AddSequential(new DriveForwardAtSpeed(60), 5.0);
	/*AddSequential(new AutoDriveDistance(-70.75));
	if (DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed)
		AddSequential(new AutoDriveTurn(-60));
	else
		AddSequential(new AutoDriveTurn(60));
	AddSequential(new AutoDriveDistance(-73.5));
	AddSequential(new MoveGearOntoLift(), 5);*/
}

