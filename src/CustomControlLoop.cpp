#include "CustomControlLoop.h"
#include "RobotMap.h"
#include "Robot.h"
#include <fstream>
#include <iostream>

bool CustomControlLoop::running;
int CustomControlLoop::time_interval;
int CustomControlLoop::ticker;

double CustomControlLoop::kTurn;
double CustomControlLoop::kP;
double CustomControlLoop::kI;
double CustomControlLoop::kD;
double CustomControlLoop::kF;
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
	time_interval = 10;
	kTurn = 0;
	kP = 0;
	kI = 0;
	kD = 0;
	kF = 0;
}

//Start the control loop (is separate from Loop() to avoid giving direct access to the loop, which could cause problems).
void CustomControlLoop::StartLoop()
{
	running = true;
	loop_thread = std::thread (Loop);
}


void CustomControlLoop::Loop()
{
	std::vector<SpeedPoint> dataStorage (0);
	std::vector<FullDataPoint> fDataStorage (0);
	std::vector<VoltPoint> vDataStorage (0);
	int time_start = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point stop_time = std::chrono::system_clock::now();
	int lastPosL = Robot::drive->GetLPosition();
	int lastPosR = Robot::drive->GetRPosition();
	double pause = 0.005;
	ticker = 0;

	if (pMode == PlayMode::SPEED_PROFILE)//Set proper control mode and constants, load up speed profile from path,
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
		RobotMap::driverDrive1->SetCloseLoopRampRate(2.5);
		RobotMap::driverDrive1->SetCloseLoopRampRate(2.5);

		std::ifstream inputFile;
		inputFile.open(filePath + inputFileName);
		printf("%s\n", (filePath + inputFileName).c_str());
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

		std::ifstream inputFile;
		inputFile.open(filePath + inputFileName);

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

	while (running)
	{
		current_time = std::chrono::system_clock::now();
		int current_time_ms = current_time.time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		int time_diff = current_time_ms - time_start;

		if (rMode == RecordMode::FULL_PROFILE)
		{

		}
		else if (rMode == RecordMode::SPEED_PROFILE)
		{
			SpeedPoint d;

			d.lSpeed = RobotMap::drivelDrive1->GetSetpoint();//RobotMap::drivelDrive1->GetSpeed() / 5;//(currentLSpeed + lastLSpeed) / 2.0;
			d.rSpeed = RobotMap::driverDrive1->GetSetpoint();//RobotMap::driverDrive1->GetSpeed() / 5;//(currentRSpeed + lastRSpeed) / 2.0;
			d.lPos = RobotMap::drivelDrive1->GetEncPosition() - lastPosL;
			d.rPos = RobotMap::driverDrive1->GetEncPosition() - lastPosR;
			lastPosL += d.lPos;
			lastPosR += d.rPos;

			d.angle = RobotMap::driveahrs->GetYaw();
			d.dur = time_interval * 1.0;
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

		}
		else if (pMode == PlayMode::SPEED_PROFILE)
		{
			if (ticker < dataStorage.size())
			{
				double angleError = Robot::drive->GetYaw() - dataStorage[ticker].angle;
				double aCorr = 0;
				Robot::drive->TankDrive(dataStorage[ticker].lSpeed + aCorr, -1 * dataStorage[ticker].rSpeed - aCorr);
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
		stop_time = current_time + std::chrono::milliseconds(time_interval);
		std::this_thread::sleep_until(stop_time);

		if (DriverStation::GetInstance().IsDisabled() || (rMode == RecordMode::NONE && pMode == PlayMode::NONE))
			running = false;
	}

	if (rMode == RecordMode::SPEED_PROFILE)
	{
		std::ofstream outputFile;
		outputFile.open(filePath + outputFileName);
		SmartDashboard::PutString("FILEPATH:", filePath + outputFileName );
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

