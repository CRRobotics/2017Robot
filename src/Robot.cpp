#include <memory>

#include "MrinalsControlLoop.h"
#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/Drive/AutoDriveDistance.h"
#include "Commands/Drive/AutoDriveSpeed.h"
#include "Commands/Drive/AutoDriveTurn.h"
#include "CommandBase.h"
#include "Robot.h"

std::shared_ptr<OI> Robot::oi;
std::shared_ptr<Drive> Robot::drive;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Gear> Robot::gear;
std::shared_ptr<Climbing> Robot::climbing;
std::shared_ptr<Acquisition> Robot::acquisition;
std::shared_ptr<Storage> Robot::storage;
Robot::TestMode Robot::tMode;
std::shared_ptr<NetworkTable> Robot::table;

std::unique_ptr<frc::Command> autonomousCommand;

void Robot::RobotInit() {
	table = NetworkTable::GetTable("vision");
	MrinalsControlLoop::InitializeValues();
	tMode = TestMode::NONE;
	RobotMap::init();
	oi.reset(new OI);
	drive.reset(new Drive());
	shooter.reset(new Shooter());
	gear.reset(new Gear());
	climbing.reset(new Climbing());
	acquisition.reset(new Acquisition());
	storage.reset(new Storage());
	SmartDashboard::PutNumber("test_pCons", 0.0);
	SmartDashboard::PutNumber("test_iCons", 0.0);
	SmartDashboard::PutNumber("test_dCons", 0.0);
	SmartDashboard::PutNumber("test_fCons", 0.0);
	SmartDashboard::PutNumber("test_setPoint", 0.0);
	switch (tMode)
	{
		case TestMode::NONE:
			SmartDashboard::PutString("test_mode", "none");
		break;
		case TestMode::DRIVE_SPEED:
			SmartDashboard::PutString("test_mode", "drive_speed");
			SmartDashboard::PutData("test_drive_speed", new AutoDriveSpeed());
		break;
		case TestMode::DRIVE_TURN_SPEED:
			SmartDashboard::PutString("test_mode", "drive_turn_speed");
			SmartDashboard::PutNumber("test_max_speed", 0);
			SmartDashboard::PutNumber("test_slow_start", 0);
			SmartDashboard::PutNumber("test_slow_end", 0);
			SmartDashboard::PutData("test_turn_to_setPoint", new AutoDriveTurn(0));
		break;
		case TestMode::DRIVE_POSITION:
			SmartDashboard::PutString("test_mode", "drive_speed_position");
			SmartDashboard::PutNumber("test_max_speed", 0);
			SmartDashboard::PutNumber("test_slow_start", 0);
			SmartDashboard::PutNumber("test_slow_end", 0);
			SmartDashboard::PutData("test_drive_to_setPoint", new AutoDriveDistance(0));
		break;
		case TestMode::DRIVE_MOTION_PROFILE:
			SmartDashboard::PutString("test_mode", "drive_motion_profile");
		break;
		case TestMode::SHOOTER_SPEED:
			SmartDashboard::PutString("test_mode", "shooter_speed");
		break;
		case TestMode::STORAGE_SPEED:
			SmartDashboard::PutString("test_mode", "storage_speed");
		break;
	}

	bool cLeftSide = DriverStation::GetInstance().GetAlliance() == DriverStation::Alliance::kRed;
	oi->SetControllerSide(cLeftSide);
	oi->MapButtons();
}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void Robot::DisabledInit() {

	}

	void Robot::DisabledPeriodic() {
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
	void Robot::AutonomousInit() {
		/* std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", "Default");
		if (autoSelected == "My Auto") {
			autonomousCommand.reset(new MyAutoCommand());
		}
		else {
			autonomousCommand.reset(new ExampleCommand());
		} */


//		if (autonomousCommand.get() != nullptr) {
////			autonomousCommand->Start();
//		}
	}

	void Robot::AutonomousPeriodic(){
		frc::Scheduler::GetInstance()->Run();
	}

	void Robot::TeleopInit(){
		MrinalsControlLoop::recording = true;
		MrinalsControlLoop::runningMotionProfile = false;
		MrinalsControlLoop::StartLoop();
	}

	void Robot::TeleopPeriodic(){
		SmartDashboard::PutNumber("rVoltage", RobotMap::driverDrive1->GetOutputVoltage());
		frc::Scheduler::GetInstance()->Run();
		if (!MrinalsControlLoop::running && Robot::oi->GetDrivePTOOff()){
			MrinalsControlLoop::recording = false;
			MrinalsControlLoop::runningMotionProfile = true;
			MrinalsControlLoop::StartLoop();
		}
	}

	void Robot::TestPeriodic(){
		frc::LiveWindow::GetInstance()->Run();
	}



START_ROBOT_CLASS(Robot)
