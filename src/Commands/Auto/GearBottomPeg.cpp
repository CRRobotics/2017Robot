/*
 * GearBottomPeg.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Driver
 */

#include "GearBottomPeg.h"
#include "SpeedProfileReplay.h"
#include "../Drive/DriveForwardAtSpeed.h"
#include "../Drive/AutoDriveTurn.h"
#include "Delay.h"
#include "../Gear/GearOut.h"
#include "../Gear/GearIn.h"

GearBottomPeg::GearBottomPeg()//GEAR RIGHT SIDE
{
	AddSequential(new SpeedProfileReplay("gear_rSide.csv", false), 9.65);
	//AddSequential(new GearOut(), 0.5);
	AddSequential(new Delay(),0.2);
	AddSequential(new DriveForwardAtSpeed(-200), 3.0);
	AddParallel(new GearIn(), 0.5);
	//AddSequential(new AutoDriveTurn(0), 4.0);

}

