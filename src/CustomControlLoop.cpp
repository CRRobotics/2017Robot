#include "CustomControlLoop.h"
#include "RobotMap.h"
#include "Robot.h"
#include <fstream>
#include <iostream>

#define DEFAULT_INTERVAL 5000

bool CustomControlLoop::running;
int CustomControlLoop::time_interval;
unsigned int CustomControlLoop::ticker;

double CustomControlLoop::kTurn;
double CustomControlLoop::kPos;
CustomControlLoop::PlayMode CustomControlLoop::pMode;
CustomControlLoop::RecordMode CustomControlLoop::rMode;

std::string CustomControlLoop::motionProfileName;
std::thread CustomControlLoop::loop_thread;
std::string CustomControlLoop::inputFileName;
std::string CustomControlLoop::outputFileName;
std::string CustomControlLoop::filePath = "/home/lvuser/MatchData/";



void CustomControlLoop::InitializeValues()
{
	running = false;
	time_interval = DEFAULT_INTERVAL;
	kTurn = 0;
}

//Start the control loop (is separate from Loop() to avoid giving direct access to the loop, which could cause problems).
void CustomControlLoop::StartLoop()
{
	running = true;
	loop_thread = std::thread (Loop);
}


void CustomControlLoop::Loop()
{
	if (!Robot::drive->BothEncodersPresent())
		return;
	std::vector<SpeedPoint> dataStorage (0);
	std::vector<FullDataPoint> fDataStorage (0);
	std::vector<VoltPoint> vDataStorage (0);
	int time_start = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point stop_time = std::chrono::system_clock::now();
	int lastPosL = Robot::drive->GetLPosition();
	int lastPosR = Robot::drive->GetRPosition();
	ticker = 0;
	time_interval = DEFAULT_INTERVAL;
	try
	{
		std::ifstream inputFile;
		inputFile.open(filePath + inputFileName);
		if (pMode == PlayMode::FULL_PROFILE)
		{
			Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
			Robot::shooter->ChangeControlMode(CANTalon::ControlMode::kSpeed);

			std::string kPString;
			std::string kIString;
			std::string kDString;
			std::string kFString;
			std::string rampString;
			std::getline(inputFile, kPString, ',');
			std::getline(inputFile, kIString, ',');
			std::getline(inputFile, kDString, ',');
			std::getline(inputFile, kFString, ',');
			std::getline(inputFile, rampString, ',');
			Robot::drive->SetPIDF(std::strtod(kPString.c_str(), NULL), std::strtod(kIString.c_str(), NULL),
									std::strtod(kDString.c_str(), NULL), std::strtod(kFString.c_str(), NULL));
			Robot::drive->SetDriveRampRate(std::strtod(rampString.c_str(), NULL));

			std::string lString;
			std::string rString;
			std::string aString;
			std::string flywheelString;
			std::string storageString;
			std::string hopperString;
			std::string gearMechString;
			std::string highGearString;
			std::string shooterAngleString;
			std::string shooterGatesString;
			std::string durString;
			std::string timeString;
			while (std::getline(inputFile, lString, ','))
			{
				std::getline(inputFile, rString, ',');
				std::getline(inputFile, aString, ',');
				std::getline(inputFile, flywheelString, ',');
				std::getline(inputFile, storageString, ',');
				std::getline(inputFile, hopperString, ',');
				std::getline(inputFile, gearMechString, ',');
				std::getline(inputFile, highGearString, ',');
				std::getline(inputFile, shooterAngleString, ',');
				std::getline(inputFile, shooterGatesString, ',');
				std::getline(inputFile, durString, ',');
				std::getline(inputFile, timeString, ',');

				double lSpd = std::strtod(lString.c_str(), NULL);
				double rSpd = std::strtod(rString.c_str(), NULL);
				double angle = std::strtod(aString.c_str(), NULL);
				double flywheel = std::strtod(flywheelString.c_str(), NULL);
				double storage = std::strtod(storageString.c_str(), NULL);
				bool hopper = hopperString == "true";
				bool gearMech = gearMechString == "true";
				bool highGear = highGearString == "true";
				bool shooterAngle = shooterAngleString == "true";
				bool shooterGates = shooterGatesString == "true";
				double dur = std::strtod(durString.c_str(), NULL);
				double timeStamp = std::strtod(timeString.c_str(), NULL);

				FullDataPoint f;
				f.lSpeed = lSpd;
				f.rSpeed = rSpd;
				f.angle = angle;
				f.shooterSpeed = flywheel;
				f.storageVoltage = storage;
				f.hopperOpen = hopper;
				f.gearMech = gearMech;
				f.highGear = highGear;
				f.shooterHigh = shooterAngle;
				f.shooterGates = shooterGates;
				f.dur = dur;
				f.timeStamp = timeStamp;

				fDataStorage.push_back(f);
			}
			inputFile.close();
		}
		else if (pMode == PlayMode::SPEED_PROFILE)//Set proper control mode and constants, load up speed profile from path,
		{
			Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);

			std::string kPString;
			std::string kIString;
			std::string kDString;
			std::string kFString;
			std::string rampString;
			std::getline(inputFile, kPString, ',');
			std::getline(inputFile, kIString, ',');
			std::getline(inputFile, kDString, ',');
			std::getline(inputFile, kFString, ',');
			std::getline(inputFile, rampString, ',');
			Robot::drive->SetPIDF(std::strtod(kPString.c_str(), NULL), std::strtod(kIString.c_str(), NULL),
									std::strtod(kDString.c_str(), NULL), std::strtod(kFString.c_str(), NULL));
			Robot::drive->SetDriveRampRate(std::strtod(rampString.c_str(), NULL));

			std::string lString;
			std::string rString;
			std::string aString;
			std::string lPosString;
			std::string rPosString;
			std::string durString;
			std::string timeString;
			while (std::getline(inputFile, lString, ','))
			{
				std::getline(inputFile, rString, ',');
				std::getline(inputFile, aString, ',');
				std::getline(inputFile, lPosString, ',');
				std::getline(inputFile, rPosString, ',');
				std::getline(inputFile, durString, ',');
				std::getline(inputFile, timeString, ',');

				double lSpd = std::strtod(lString.c_str(), NULL);
				double rSpd = std::strtod(rString.c_str(), NULL);
				double angle = std::strtod(aString.c_str(), NULL);
				double lPos = std::strtod(lPosString.c_str(), NULL);
				double rPos = std::strtod(rPosString.c_str(), NULL);
				double dur = std::strtod(durString.c_str(), NULL);
				double timeStamp = std::strtod(timeString.c_str(), NULL);
				SpeedPoint d;
				d.lSpeed = lSpd;
				d.rSpeed = rSpd;
				d.angle = angle;
				d.lPos = lPos;
				d.rPos = rPos;
				d.dur = dur;
				d.timeStamp = timeStamp;
				dataStorage.push_back(d);
			}
			inputFile.close();
		}
		else if (pMode == PlayMode::VOLT_PROFILE)//Load up voltage profile from path
		{
			RobotMap::driverDrive1->SetControlMode(CANTalon::ControlMode::kVoltage);
			RobotMap::drivelDrive1->SetControlMode(CANTalon::ControlMode::kVoltage);

			std::string lVolt;
			std::string rVolt;
			std::string aString;

			while (std::getline(inputFile, lVolt, ','))
			{
				std::getline(inputFile, rVolt, ',');
				std::getline(inputFile, aString, ',');
				VoltPoint d;
				d.lV = std::strtod(lVolt.c_str(), NULL);
				d.rV = std::strtod(rVolt.c_str(), NULL);
				d.angle = std::strtod(aString.c_str(), NULL);
				vDataStorage.push_back(d);
			}
		}
	}
	catch(...)
	{
		running = false;
		DriverStation::ReportError("Could not load motion profile...");
	}

	while (running)
	{
		current_time = std::chrono::system_clock::now();
		int current_time_ms = current_time.time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		int time_diff = current_time_ms - time_start;

		if (rMode == RecordMode::FULL_PROFILE)
		{
			FullDataPoint f;

			f.lSpeed = RobotMap::drivelDrive1->GetSetpoint();//Robot::drive->GetLSpeed();
			f.rSpeed = RobotMap::driverDrive1->GetSetpoint();//Robot::drive->GetRSpeed();
			f.angle = Robot::drive->GetYaw();
			f.dur = time_interval / 1000000.0;
			f.timeStamp = time_diff * 1.0;
			f.hopperOpen = RobotMap::doorPiston->Get();
			f.gearMech = Robot::gear->GetExtended();
			f.highGear = Robot::drive->GetGear();
			f.shooterHigh = RobotMap::shooterangleShift->Get();
			f.shooterGates = RobotMap::leftGate->Get() || RobotMap::rightGate->Get();
			f.shooterSpeed = Robot::shooter->GetFlywheelSpeed();
			f.storageVoltage = RobotMap::storageballControlMotor->GetOutputVoltage();
			fDataStorage.push_back(f);
		}
		else if (rMode == RecordMode::SPEED_PROFILE)
		{
			SpeedPoint d;

			if (Robot::side)
			{
				//d.lSpeed = RobotMap::drivelDrive1->GetSetpoint();
				d.lSpeed = Robot::drive->GetLSpeed();
				//d.rSpeed = RobotMap::driverDrive1->GetSetpoint();
				d.rSpeed = Robot::drive->GetRSpeed();
				d.lPos = Robot::drive->GetLPosition() - lastPosL;
				d.rPos = Robot::drive->GetRPosition() - lastPosR;
				lastPosL += d.lPos;
				lastPosR += d.rPos;
				d.angle = RobotMap::driveahrs->GetYaw();
			}
			else
			{
				//d.rSpeed = RobotMap::drivelDrive1->GetSetpoint();
				d.rSpeed = Robot::drive->GetLSpeed();
				//d.lSpeed = RobotMap::driverDrive1->GetSetpoint();
				d.lSpeed = Robot::drive->GetRSpeed();
				d.rPos = Robot::drive->GetLPosition() - lastPosL;
				d.lPos = Robot::drive->GetRPosition() - lastPosR;
				lastPosL += d.lPos;
				lastPosR += d.rPos;
				d.angle = -1 * RobotMap::driveahrs->GetYaw();
			}

			d.dur = time_interval / 1000000.0;
			d.timeStamp = time_diff * 1.0;
			dataStorage.push_back(d);
		}
		else if (rMode == RecordMode::VOLT_PROFILE)
		{
			VoltPoint d;
			d.lV = RobotMap::drivelDrive1->GetOutputVoltage();
			d.rV = RobotMap::driverDrive1->GetOutputVoltage();
			d.angle = Robot::drive->GetYaw();
			vDataStorage.push_back(d);
		}


		if (pMode == PlayMode::FULL_PROFILE)
		{
			if (ticker < dataStorage.size())
			{
				FullDataPoint f = fDataStorage[ticker];
				double angleError = Robot::drive->GetYaw() - f.angle;
				double aCorr = 0;
				Robot::drive->TankDrive(f.lSpeed + aCorr, -1 * (f.rSpeed - aCorr));
				Robot::storage->MoveStorage(f.storageVoltage);
				RobotMap::shooterflywheel->Set(f.shooterSpeed);

				if (Robot::drive->GetGear() != f.highGear)
					Robot::drive->ChangeGear(f.highGear);
				if (RobotMap::doorPiston->Get() != f.hopperOpen)
					RobotMap::doorPiston->Set(f.hopperOpen);
				if (RobotMap::gearpiston->Get() != f.gearMech)
					RobotMap::gearpiston->Set(f.gearMech);
				if (RobotMap::shooterangleShift->Get() != f.shooterHigh)
					RobotMap::shooterangleShift->Set(f.shooterHigh);
				if (RobotMap::leftGate->Get() != f.shooterGates || RobotMap::rightGate->Get() != f.shooterGates)
				{
					RobotMap::leftGate->Set(f.shooterGates);
					RobotMap::rightGate->Set(f.shooterGates);
				}
				time_interval = (int)(f.dur * 1000000);
			}
			else
			{
				Robot::drive->TankDrive(0,0);
				pMode = PlayMode::NONE;
			}
		}
		else if (pMode == PlayMode::SPEED_PROFILE)
		{
			if (ticker < dataStorage.size())
			{
				double lSpeed;
				double rSpeed;
				double yawAngle;

				SpeedPoint d = dataStorage[ticker];
				if (Robot::side)
				{
					lSpeed = d.lSpeed;
					rSpeed = d.rSpeed;
					yawAngle = d.angle;
				}
				else
				{
					lSpeed = d.rSpeed;
					rSpeed = d.lSpeed;
					yawAngle = -1 * d.angle;
				}
				double angleError = angle_diff(Robot::drive->GetYaw(), yawAngle);
				SmartDashboard::PutNumber("Angle Error", angleError);
				double aCorr = 0 * angleError;
				double lPosError = 0;
				double rPosError = 0;
				if (ticker > 0)
				{
					double dl = Robot::drive->GetLPosition() - lastPosL;
					double dr = Robot::drive->GetRPosition() - lastPosR;
					lastPosL += dl;
					lastPosR += dr;
					lPosError = d.lPos - dl;
					rPosError = d.rPos - dr;
				}
				Robot::drive->TankDrive(d.lSpeed + aCorr, -1 * (d.rSpeed - aCorr));
				time_interval = (int)(d.dur * 1000000);
			}
			else
			{
				Robot::drive->TankDrive(0, 0);
				pMode = PlayMode::NONE;
			}
		}
		else if (pMode == PlayMode::VOLT_PROFILE)
		{
			if (ticker < vDataStorage.size())
			{
				double angleError = Robot::drive->GetYaw() - dataStorage[ticker].angle;
				double aCorr = 0;
				Robot::drive->TankDrive(vDataStorage[ticker].lV + aCorr, vDataStorage[ticker].rV - aCorr);
			}
			else
			{
				Robot::drive->TankDrive(0, 0);
				pMode = PlayMode::NONE;
			}
		}

		ticker++;
		stop_time = current_time + std::chrono::microseconds(time_interval);
		std::this_thread::sleep_until(stop_time);

		if (DriverStation::GetInstance().IsDisabled() || (rMode == RecordMode::NONE && pMode == PlayMode::NONE))
			running = false;
	}

	if (rMode == RecordMode::SPEED_PROFILE)
	{
		std::ofstream outputFile;
		outputFile.open(filePath + outputFileName);
		SmartDashboard::PutString("FILEPATH:", filePath + outputFileName );
		outputFile << RobotMap::driverDrive1->GetP() << ", ";
		outputFile << RobotMap::driverDrive1->GetI() << ", ";
		outputFile << RobotMap::driverDrive1->GetD() << ", ";
		outputFile << RobotMap::driverDrive1->GetF() << ", ";
		outputFile << Robot::drive->GetDriveRampRate() << ",\n";
		for (unsigned int i = 0; i < dataStorage.size(); i++)
		{
			outputFile << dataStorage[i].lSpeed << ", " << dataStorage[i].rSpeed << ",";
			outputFile << dataStorage[i].angle << ", " << dataStorage[i].lPos << ", " << dataStorage[i].rPos << ", ";
			outputFile << dataStorage[i].dur << ", " << dataStorage[i].timeStamp << ",\n";
		}
		outputFile.close();
	}
	else if (rMode == RecordMode::FULL_PROFILE)
	{
		std::ofstream outputFile;
		outputFile.open(filePath + outputFileName);
		SmartDashboard::PutString("FILEPATH:", filePath + outputFileName);
		outputFile << RobotMap::driverDrive1->GetP() << ", ";
		outputFile << RobotMap::driverDrive1->GetI() << ", ";
		outputFile << RobotMap::driverDrive1->GetD() << ", ";
		outputFile << RobotMap::driverDrive1->GetF() << ", ";
		outputFile << Robot::drive->GetDriveRampRate() << ",\n";
		for (unsigned int i = 0; i < fDataStorage.size(); i++)
		{
			FullDataPoint f = fDataStorage[i];
			outputFile << f.lSpeed << ", " << f.rSpeed << ", " << f.angle << ", ";
			outputFile << f.shooterSpeed << ", " << f.storageVoltage << ", " << f.hopperOpen << ", ";
			outputFile << f.gearMech << ", " << f.highGear << ", " << f.shooterHigh << ", " << f.shooterGates << ", ";
			outputFile << f.dur << ", " << f.timeStamp << ",\n";
		}
		outputFile.close();
	}
	else if (rMode == RecordMode::VOLT_PROFILE)
	{
		std::ofstream outputFile;
		outputFile.open(filePath + outputFileName);
		for (unsigned int i = 0; i < vDataStorage.size(); i++)
		{
			outputFile << vDataStorage[i].lV << ", " << vDataStorage[i].rV << ", " << vDataStorage[i].angle << ",\n";
		}
		outputFile.close();
	}

	loop_thread.detach();
}

