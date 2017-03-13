#include "MrinalsControlLoop.h"
#include "RobotMap.h"
#include "Robot.h"
#include <fstream>
#include <iostream>

bool MrinalsControlLoop::recording;
bool MrinalsControlLoop::runningMotionProfile;
bool MrinalsControlLoop::running;
int MrinalsControlLoop::time_interval;
int MrinalsControlLoop::ticker;

std::string MrinalsControlLoop::motionProfileName;
std::thread MrinalsControlLoop::loop_thread;

struct DataPoint
{
	double lSpeed;
	double rSpeed;
	double angle;
	double dur;
	double timeStamp;
};

void MrinalsControlLoop::InitializeValues(){
	running = false;
	time_interval = 20;
}

//record lSpeed, rSpeed, angle, time interval, time
void MrinalsControlLoop::StartLoop(){
	running = true;
	ticker = 0;
	loop_thread = std::thread (Loop);
}
void MrinalsControlLoop::Loop()
{
	std::vector<DataPoint> dataStorage (0);
	int time_start = std::chrono::system_clock::now().time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
	std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
	std::chrono::system_clock::time_point stop_time = std::chrono::system_clock::now();
	double lastLSpeed = Robot::drive->GetLEncoderRate();
	double lastRSpeed = Robot::drive->GetREncoderRate();
	int ticker = 0;
	if (runningMotionProfile)
	{
		Robot::drive->SetControlMode(Drive::DriveControlMode::Voltage);

		std::ifstream inputFile;
		inputFile.open("/home/lvuser/MatchData/MrinalLoggerData.txt");
		std::string lString;
		std::string rString;
		while (std::getline(inputFile, lString, ',')){
			std::getline(inputFile, rString, ',');
			double lSpd = std::strtod(lString.c_str(), NULL);
			double rSpd = std::strtod(rString.c_str(), NULL);
			DataPoint d;
			d.lSpeed = lSpd;
			d.rSpeed = rSpd;
			dataStorage.push_back(d);
		}
		inputFile.close();
	}

	while (running)
	{
		current_time = std::chrono::system_clock::now();
		int time_diff = current_time.time_since_epoch().count() * 1000 * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den - time_start;

		if (recording)
		{
			DataPoint d;
			double currentLSpeed = Robot::drive->GetLEncoderRate();
			double currentRSpeed = Robot::drive->GetREncoderRate();
			d.lSpeed = Robot::oi->GetYDriverL() * fabs(Robot::oi->GetYDriverL());//(currentLSpeed + lastLSpeed) / 2.0;
			d.rSpeed = Robot::oi->GetYDriverR() * fabs(Robot::oi->GetYDriverR());//(currentRSpeed + lastRSpeed) / 2.0;
			lastLSpeed = currentLSpeed;
			lastRSpeed = currentRSpeed;
			d.angle = RobotMap::driveahrs->GetYaw();
			d.dur = time_interval * 1.0;
			d.timeStamp = time_diff * 1.0;
			dataStorage.push_back(d);
			printf("speed %f\n%f\n",  d.lSpeed, d.rSpeed);
		}

		if (runningMotionProfile)
		{
			if (ticker < dataStorage.size())
			{
				Robot::drive->TankDrive(dataStorage[ticker].lSpeed, dataStorage[ticker].rSpeed);
				printf("speed %f, %f", dataStorage[ticker].lSpeed, dataStorage[ticker].rSpeed);
			}
		}

		ticker++;
//		printf("ticker %d\n", ticker);

		stop_time = current_time + std::chrono::milliseconds(time_interval);
		std::this_thread::sleep_until(stop_time);

		if (Robot::oi->GetDrivePTOOn())
					running = false;
	}

	std::ofstream outputFile;
	outputFile.open("/home/lvuser/MatchData/MrinalLoggerData.txt");
	//outputFile << "\n\n\n NEW MATCH\n";
	for (unsigned int i = 0; i < dataStorage.size(); i++)
	{
		outputFile << dataStorage[i].lSpeed << ", " << dataStorage[i].rSpeed << ", ";
		//outputFile << dataStorage[i].angle << ", " << dataStorage[i].dur << ", ";
		//outputFile << dataStorage[i].timeStamp << ",\n";
	}
	outputFile.close();

	loop_thread.detach();
}

