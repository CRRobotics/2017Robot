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
	time_interval = 10;
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
	int ticker = 0;
	double kAngle = 0;
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
			double lSpd = std::strtod(lString.c_str(), NULL);
			double rSpd = std::strtod(rString.c_str(), NULL);
			double angle = std::strtod(aString.c_str(), NULL);
			DataPoint d;
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
			DataPoint d;
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
}

