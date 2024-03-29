#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <CustomControlLoop.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/KitbotTesting/PositionTracker.h"
#include "Commands/KitbotTesting/PegTest.h"
#include "Commands/Auto/GearTopPeg.h"
#include "Commands/Auto/GearBottomPeg.h"
#include "Commands/Auto/MiddlePegAndShootRecorded.h"
#include "Commands/Auto/BottomPegAndShoot.h"
#include "Commands/Auto/VoltProfileReplay.h"
#include "Commands/Auto/SpeedProfileReplay.h"
#include "Commands/Auto/SpeedProfileRecord.h"
#include "Commands/Auto/VisionGearPlacement/VisionGearPlacement.h"
#include "Commands/Drive/AutoDriveDistance.h"
#include "Commands/Drive/AutoDriveSpeed.h"
#include "Commands/Drive/AutoDriveTurn.h"
#include "Commands/Shooter/FireBalls.h"
#include "Commands/Auto/GearMiddlePeg.h"
#include "Commands/Auto/HopperAndShoot.h"
#include "Commands/LEDs/LEDRefresh.h"
#include "CommandBase.h"
#include "Robot.h"
#include "Commands/Shooter/StopShooter.h"

std::shared_ptr<OI> Robot::oi;
std::shared_ptr<Drive> Robot::drive;
std::shared_ptr<Shooter> Robot::shooter;
std::shared_ptr<Gear> Robot::gear;
std::shared_ptr<Climbing> Robot::climbing;
std::shared_ptr<Acquisition> Robot::acquisition;
std::shared_ptr<Storage> Robot::storage;
std::shared_ptr<GearFloorAcq> Robot::floorAcq;
std::shared_ptr<LEDs> Robot::leds;
Robot::TestMode Robot::tMode;
std::shared_ptr<NetworkTable> Robot::table;
bool Robot::oiMapped;
bool Robot::yawReset;
bool Robot::side;

std::unique_ptr<frc::SendableChooser<std::string>> Robot::sideSelection;
std::unique_ptr<frc::SendableChooser<std::string>> Robot::autoSelection;
std::unique_ptr<frc::Command> Robot::autonomousCommand;

void Robot::RobotInit()
{
	sideSelection.reset(new frc::SendableChooser<std::string>());
	sideSelection->AddDefault("red", "r");
	sideSelection->AddObject("blue", "b");

	SmartDashboard::PutNumber("angle error", 0);
	SmartDashboard::PutNumber("drive_speed_error_r", 0);
	SmartDashboard::PutNumber("drive_speed_error_l", 0);


	autoSelection.reset(new frc::SendableChooser<std::string>());
	autoSelection->AddDefault("Drive Forward (Gear Middle Peg)", "gear_middle");
	autoSelection->AddObject("Gear Bottom (Right)", "gear_bot");
	autoSelection->AddObject("Gear Top (Left)", "gear_top");
	autoSelection->AddObject("None", "none");
	autoSelection->AddObject("Gear Middle Peg Recorded", "mpegrecorded");
	autoSelection->AddObject("BottomPegAndShoot", "bpegshoot");
	autoSelection->AddObject("HopperAndShoot", "hshoot");
	//autoSelection->AddDefault("Drive Forward (Gear Middle Peg)", *(new GearMiddlePeg()));
	//autoSelection->AddObject("Gear Bottom", *(new SpeedProfileReplay("gear_bot.csv", false)));
	//autoSelection->AddObject("Gear Top", *(new SpeedProfileReplay("gear_top.csv", false)));

	table = NetworkTable::GetTable("vision");
	CustomControlLoop::InitializeValues();
	tMode = TestMode::AUTO_GEAR;
	RobotMap::init();
	oi.reset(new OI);
	drive.reset(new Drive());
	shooter.reset(new Shooter());
	gear.reset(new Gear());
	climbing.reset(new Climbing());
	acquisition.reset(new Acquisition());
	storage.reset(new Storage());
	leds.reset(new LEDs(30));
	floorAcq.reset(new GearFloorAcq());
	SmartDashboard::PutData("Replay speed recording", new SpeedProfileReplay("", true));
	SmartDashboard::PutData("Create speed recording", new SpeedProfileRecord());
	SmartDashboard::PutString("input_file_name", "paulsucks.csv");
	SmartDashboard::PutString("output_file_name", "paulsucks.csv");
	SmartDashboard::PutNumber("test_pCons", 0.0);
	SmartDashboard::PutNumber("test_iCons", 0.0);
	SmartDashboard::PutNumber("test_dCons", 0.0);
	SmartDashboard::PutNumber("test_fCons", 0.0);
	SmartDashboard::PutNumber("test_setPoint", 0.0);
	SmartDashboard::PutData("Side Selection", sideSelection.get());
	SmartDashboard::PutData("Auto Selection", autoSelection.get());
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
			SmartDashboard::PutNumber("test_min_speed", 0);
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
			SmartDashboard::PutNumber("shooter_speed", RobotMap::shooterflywheel->GetSpeed());
		break;
		case TestMode::STORAGE_SPEED:
			SmartDashboard::PutString("test_mode", "storage_speed");
		break;
		case TestMode::AUTO_GEAR:
			SmartDashboard::PutNumber("target_gear_angle", 0.0);
			SmartDashboard::PutNumber("target_gear_dist", 0.0);
			SmartDashboard::PutData("Auto Gear Placement", new VisionGearPlacement());
		break;
	}

	side = false;//TRUE = RED, FALSE = BLUE
	oi->SetControllerSide(true);
	oiMapped = false;
	oi->MapButtons();
	yawReset = false;
	PrintOrResetYaw();
	CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
	CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
	CustomControlLoop::running = false;

	leds->ChangeMode(LEDs::LEDMode::RED_BLINK);
	LEDRefresh::defaultMode = LEDs::LEDMode::RED_BLINK;
}

	/**
	 * This function is called once each time the robot enters Disabled mode.
	 * You can use it to reset any subsystem information you want to clear when
	 * the robot is disabled.
	 */
	void Robot::DisabledInit()
	{
		leds->ChangeMode(LEDs::LEDMode::RED_BLINK);
		LEDRefresh::defaultMode = LEDs::LEDMode::RED_BLINK;

	}

	void Robot::DisabledPeriodic()
	{
		frc::Scheduler::GetInstance()->Run();
		((LEDRefresh *)(leds->GetDefaultCommand()))->ExecuteCopy();
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
	void Robot::AutonomousInit()
	{
		LEDRefresh::defaultMode = LEDs::LEDMode::PATRIOTIC;
		Robot::leds->ChangeMode(LEDs::LEDMode::PATRIOTIC);

		RobotMap::leftGate->Set(true);
		RobotMap::rightGate->Set(true);
		Robot::gear->RetractGear();
		PrintOrResetYaw();
		side = std::string(sideSelection->GetSelected()) == "r";
		std::string auto_mode = autoSelection->GetSelected();
		if (auto_mode == "none")
		{
			autonomousCommand.reset(new PegTest());
		}
		else if(auto_mode == "hshoot")
		{
			autonomousCommand.reset(new HopperAndShoot());
		}
		else if (auto_mode == "gear_middle")
		{
			autonomousCommand.reset(new GearMiddlePeg());
		}
		else if (auto_mode == "gear_top")
		{
			Robot::side = true;
			autonomousCommand.reset(new GearTopPeg());
		}
		else if (auto_mode == "gear_bot")
		{
			Robot::side = false;
			autonomousCommand.reset(new GearBottomPeg());
		}
		else if (auto_mode == "mpegrecorded")
		{
			autonomousCommand.reset(new MiddlePegAndShootRecorded());
		}
		else if (auto_mode == "bpegshoot")
		{
			autonomousCommand.reset(new BottomPegAndShoot());
		}
		else
		{
			autonomousCommand.reset(new SpeedProfileReplay(auto_mode, false));
		}

		if (autonomousCommand != nullptr)
			autonomousCommand->Start();

	}

	void Robot::AutonomousPeriodic()
	{
		frc::Scheduler::GetInstance()->Run();
	}

	void Robot::TeleopInit()
	{
		LEDRefresh::defaultMode = LEDs::LEDMode::RED;
		Robot::leds->ChangeMode(LEDs::LEDMode::RED);
		//Robot::floorAcq->RaiseSystem();
		//(new PositionTracker())->Start();
		PrintOrResetYaw();
		//side = sideSelection->GetSelected().c_str() == "r";

		CustomControlLoop::outputFileName = SmartDashboard::GetString("output_file_name", "nameless.csv");
		CustomControlLoop::inputFileName = SmartDashboard::GetString("input_file_name", "nameless.txt");
		CustomControlLoop::rMode = CustomControlLoop::RecordMode::NONE;
		CustomControlLoop::pMode = CustomControlLoop::PlayMode::NONE;
		//CustomControlLoop::StartLoop();
		//RobotMap::leftGate->Set(true);
		//RobotMap::rightGate->Set(true);
	}

	void Robot::TeleopPeriodic()
	{
		//SmartDashboard::PutNumber("shooter_error", Robot::shooter->GetSpeedError());
		SmartDashboard::PutBoolean("Gear Sensor", Robot::floorAcq->GearPresent());
		SmartDashboard::PutNumber("Robot yaw", Robot::drive->GetYaw());
		//SmartDashboard::PutNumber("test_speed_error", RobotMap::drivelDrive1->GetClosedLoopError());
		//SmartDashboard::PutNumber("test_speed_speed", RobotMap::drivelDrive1->GetSpeed());
		//SmartDashboard::PutBoolean("NavX Callibrating", RobotMap::driveahrs->IsCalibrating());
		//SmartDashboard::PutBoolean("Profile recording", CustomControlLoop::rMode != CustomControlLoop::RecordMode::NONE);
		frc::Scheduler::GetInstance()->Run();
	}

	void Robot::PrintOrResetYaw(){
		if (RobotMap::driveahrs->IsConnected() && !RobotMap::driveahrs->IsCalibrating())
		{
			if (!yawReset)
			{
				Robot::drive->ResetYaw();
				//SmartDashboard::PutBoolean("Reset Yaw!", true);
				if (fabs(Robot::drive->GetYaw()) < 2)
					yawReset = true;
			}
			else
				SmartDashboard::PutNumber("Robot yaw", Robot::drive->GetYaw());
		}
	}

	void Robot::TestPeriodic()
	{
		frc::LiveWindow::GetInstance()->Run();
	}



START_ROBOT_CLASS(Robot)
