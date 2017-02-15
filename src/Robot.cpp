#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Robot.h"

std::unique_ptr<OI> oi;
std::shared_ptr<Drive> drive;
std::shared_ptr<Shooter> shooter;
std::shared_ptr<Gear> gear;
std::shared_ptr<Climbing> climbing;
std::shared_ptr<Acquisition> acquisition;
std::shared_ptr<Storage> storage;

std::unique_ptr<frc::Command> autonomousCommand;
frc::SendableChooser<frc::Command*> chooser;

void Robot::RobotInit() {
	// chooser.AddObject("My Auto", new MyAutoCommand());
	frc::SmartDashboard::PutData("Auto Modes", &chooser);

		RobotMap::init();
		oi.reset(new OI);
		drive.reset(new Drive());
		shooter.reset(new Shooter());
		gear.reset(new Gear());
		climbing.reset(new Climbing());
		acquisition.reset(new Acquisition());
		storage.reset(new Storage());
	}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void DisabledInit() {

	}

	void DisabledPeriodic() {
		frc::Scheduler::GetInstance()->Run();
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString code to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional commands to the
	 * chooser code above (like the commented example) or additional comparisons
	 * to the if-else structure below with additional strings & commands.
	 */
	void AutonomousInit() {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */


		if (autonomousCommand.get() != nullptr) {
			autonomousCommand->Start();
		}
	}

	void AutonomousPeriodic(){
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit(){
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (true) {
			autonomousCommand->Cancel();
		}
	}

	void TeleopPeriodic(){
		frc::Scheduler::GetInstance()->Run();
	}

	void TestPeriodic(){
		frc::LiveWindow::GetInstance()->Run();
	}



START_ROBOT_CLASS(Robot)
