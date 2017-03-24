// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"

#include "Commands/Auto/AutonomousCommand.h"
#include "Subsystems/Acquisition.h"
#include "Subsystems/Climbing.h"
#include "Subsystems/Drive.h"
#include "Subsystems/Gear.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/Storage.h"

#include "OI.h"

class Robot : public IterativeRobot {
public:

	enum class TestMode{
		NONE,
		SHOOTER_SPEED,
		STORAGE_SPEED,
		DRIVE_SPEED,
		DRIVE_TURN_SPEED,
		DRIVE_POSITION,
		DRIVE_MOTION_PROFILE
	};

	static bool side;
	static bool oiMapped;
	static bool yawReset;
	static TestMode tMode;
	std::unique_ptr<Command> autonomousCommand;
	static std::shared_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	static std::shared_ptr<Drive> drive;
    static std::shared_ptr<Shooter> shooter;
    static std::shared_ptr<Gear> gear;
    static std::shared_ptr<Climbing> climbing;
    static std::shared_ptr<Acquisition> acquisition;
    static std::shared_ptr<Storage> storage;
    static std::shared_ptr<NetworkTable> table;
    static void PrintOrResetYaw();
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};
#endif
