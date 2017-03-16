#include "MrinalsControlLoop.h"
#include "RobotMap.h"
#include "Robot.h"
#include <fstream>
#include <iostream>

bool MrinalsControlLoop::running;
int MrinalsControlLoop::time_interval;
int MrinalsControlLoop::ticker;

double MrinalsControlLoop::kTurn;
double MrinalsControlLoop::kP;
double MrinalsControlLoop::kI;
double MrinalsControlLoop::kD;
double MrinalsControlLoop::kF;
MrinalsControlLoop::PlayMode MrinalsControlLoop::pMode;
MrinalsControlLoop::RecordMode MrinalsControlLoop::rMode;

std::string MrinalsControlLoop::motionProfileName;
std::thread MrinalsControlLoop::loop_thread;
std::string MrinalsControlLoop::inputFileName;
std::string MrinalsControlLoop::outputFileName;
std::string MrinalsControlLoop::filePath = "/home/lvuser/MatchData/";
struct SpeedPoint
{
	double lSpeed;
	double rSpeed;
	int lPos;
	int rPos;
	double angle;
	double dur;
	double timeStamp;
};

struct FullDataPoint{
	double lSpeed;
	double rSpeed;
	double angle;
	double shooterSpeed;
	double storageVoltage;
	bool acqOpen;
	bool highGear;
	bool shooterHigh;
	double dur;
	double timeStamp;
};

void MrinalsControlLoop::InitializeValues(){
	running = false;
	time_interval = 10;
	kTurn = 0;
	kP = 0;
	kI = 0;
	kD = 0;
	kF = 0;
}

//record lSpeed, rSpeed, angle, time interval, time
void MrinalsControlLoop::StartLoop(){
	running = true;
	ticker = 0;
	loop_thread = std::thread (Loop);
}


void MrinalsControlLoop::Loop(){
	std::vector<SpeedPoint> dataStorage (0);
	std::vector<FullDataPoint> fDataStorage (0);
	int time_start = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point stop_time = std::chrono::system_clock::now();
	int lastPosL = Robot::drive->GetLEncoder();
	int lastPosR = Robot::drive->GetREncoder();

	if (pMode == PlayMode::SPEED_PROFILE){
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);

		std::ifstream inputFile;
		inputFile.open(filePath.append(inputFileName));

		std::string lString;
		std::string rString;
		std::string aString;
		while (std::getline(inputFile, lString, ',')){
			std::getline(inputFile, rString, ',');
			std::getline(inputFile, aString, ',');
			double lSpd = std::strtod(lString.c_str(), NULL);
			double rSpd = std::strtod(rString.c_str(), NULL);
			double angle = std::strtod(aString.c_str(), NULL);
			SpeedPoint d;
			d.lSpeed = lSpd;
			d.rSpeed = rSpd;
			d.angle = angle;
			dataStorage.push_back(d);
		}
		inputFile.close();
	}

	while (running){
		current_time = std::chrono::system_clock::now();
		int current_time_ms = current_time.time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		int time_diff = current_time_ms - time_start;

		if (rMode == RecordMode::FULL_PROFILE){

		}
		else if (rMode == RecordMode::SPEED_PROFILE){
			SpeedPoint d;
			d.lSpeed = RobotMap::drivelDrive1->GetSetpoint();//(currentLSpeed + lastLSpeed) / 2.0;
			d.rSpeed = RobotMap::driverDrive1->GetSetpoint();//(currentRSpeed + lastRSpeed) / 2.0;
			d.lPos = RobotMap::drivelDrive1->GetEncPosition() - lastPosL;
			d.rPos = RobotMap::driverDrive1->GetEncPosition() - lastPosR;
			lastPosL += d.lPos;
			lastPosR += d.rPos;

			d.angle = RobotMap::driveahrs->GetYaw();
			d.dur = time_interval * 1.0;
			d.timeStamp = time_diff * 1.0;
			dataStorage.push_back(d);
		}

		if (pMode == PlayMode::FULL_PROFILE){

		}
		else if (pMode == PlayMode::SPEED_PROFILE){
			if (ticker < dataStorage.size())
			{
				double angleError = Robot::drive->GetYaw() - dataStorage[ticker].angle;
				double aCorr = 0;
				Robot::drive->TankDrive(dataStorage[ticker].lSpeed + aCorr, dataStorage[ticker].rSpeed - aCorr);
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

	if (rMode == RecordMode::SPEED_PROFILE){
		std::ofstream outputFile;
		outputFile.open(filePath.append(outputFileName));
		for (unsigned int i = 0; i < dataStorage.size(); i++)
		{
			outputFile << dataStorage[i].lSpeed << ", " << dataStorage[i].rSpeed << ",";
			outputFile << dataStorage[i].angle << ", " << dataStorage[i].lPos << ", " << dataStorage[i].rPos << ", ";
			outputFile << dataStorage[i].dur << ", " << dataStorage[i].timeStamp << ",\n";
		}
		outputFile.close();
	}
	else if (rMode == RecordMode::FULL_PROFILE){

	}

	loop_thread.detach();
}



/*void MrinalsControlLoop::Loop()
{
	std::vector<SpeedPoint> dataStorage (0);
	int time_start = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point stop_time = std::chrono::system_clock::now();
	if (runningMotionProfile)
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);

		std::ifstream inputFile;
		inputFile.open("/home/lvuser/MatchData/MrinalLoggerData.txt");
		std::string lString;
		std::string rString;
		std::string aString;
		while (std::getline(inputFile, lString, ',')){
			std::getline(inputFile, rString, ',');
			std::getline(inputFile, aString, ',');
			double lSpd = std::strtod(lString.c_str(), NULL);
			double rSpd = std::strtod(rString.c_str(), NULL);
			double angle = std::strtod(aString.c_str(), NULL);
			SpeedPoint d;
			d.lSpeed = lSpd;
			d.rSpeed = rSpd;
			d.angle = angle;
			dataStorage.push_back(d);
		}
		inputFile.close();
	}

	while (running)
	{
		current_time = std::chrono::system_clock::now();
		int current_time_ms = current_time.time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
		int time_diff = current_time_ms - time_start;
		time_start = current_time_ms;
		if (recording)
		{
			SpeedPoint d;
			d.lSpeed = RobotMap::drivelDrive1->GetSetpoint();//(currentLSpeed + lastLSpeed) / 2.0;
			d.rSpeed = RobotMap::driverDrive1->GetSetpoint();//(currentRSpeed + lastRSpeed) / 2.0;
			d.angle = RobotMap::driveahrs->GetYaw();
			d.dur = time_interval * 1.0;
			d.timeStamp = time_diff * 1.0;
			dataStorage.push_back(d);
			printf("RECORDING %d\n", time_diff);
			//printf("speed %f\n%f\n",  d.lSpeed, d.rSpeed);
		}

		if (runningMotionProfile)
		{
			if (ticker < dataStorage.size())
			{
				double angleError = Robot::drive->GetYaw() - dataStorage[ticker].angle;
				double aCorr = 0;
				SmartDashboard::PutNumber("Yaw error", angleError);
				Robot::drive->TankDrive(dataStorage[ticker].lSpeed + aCorr, dataStorage[ticker].rSpeed - aCorr);
				printf("PLAYING %d\n", time_diff);
			}
			else
				runningMotionProfile = false;
		}

		ticker++;
//		printf("ticker %d\n", ticker);

		stop_time = current_time + std::chrono::milliseconds(time_interval);
		std::this_thread::sleep_until(stop_time);

		if (Robot::oi->GetDrivePTOOn() || DriverStation::GetInstance().IsDisabled())
					running = false;
	}

	if (recording)
	{
		std::ofstream outputFile;
		outputFile.open("/home/lvuser/MatchData/MrinalLoggerData.txt");
		//outputFile << "\n\n\n NEW MATCH\n";
		for (unsigned int i = 0; i < dataStorage.size(); i++)
		{
			outputFile << dataStorage[i].lSpeed << ", " << dataStorage[i].rSpeed << ",";
			outputFile << dataStorage[i].angle << ",\n";// << dataStorage[i].dur << ", ";
			//outputFile << dataStorage[i].timeStamp << ",\n";
		}
		outputFile.close();
	}

	loop_thread.detach();
}*/

