#ifndef SRC_CustomControlLoop_H_
#define SRC_CustomControlLoop_H_

#include <chrono>
#include <future>
#include <vector>


class CustomControlLoop
{
	public:
	enum class RecordMode{
		VOLT_PROFILE,
		FULL_PROFILE,
		SPEED_PROFILE,
		NONE
	};

	enum class PlayMode{
		VOLT_PROFILE,
		FULL_PROFILE,
		SPEED_PROFILE,
		NONE
	};

	static void InitializeValues();
	static void StartLoop();
	static void SetLoggerTime(int ms);
	static void Loop();
	static void EndLoop();

//	static bool runningMotionProfile;
//	static bool recording;
	static std::string inputFileName;
	static std::string outputFileName;
	static std::string filePath;
	static std::string motionProfileName;
	static std::thread loop_thread;
	static bool running;
	static int time_interval;
	static unsigned int ticker;
	static RecordMode rMode;
	static PlayMode pMode;


	private:
	static double kTurn;
	static double kPos;

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
		bool hopperOpen;
		bool gearMech;
		bool highGear;
		bool shooterHigh;
		bool shooterGates;
		double dur;
		double timeStamp;
	};

	struct VoltPoint{
		double lV;
		double rV;
		double angle;

	};


};


#endif /* SRC_MRINALSCustomControlLoop_H_ */
