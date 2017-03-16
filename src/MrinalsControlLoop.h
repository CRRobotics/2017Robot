#ifndef SRC_MrinalsControlLoop_H_
#define SRC_MrinalsControlLoop_H_

#include <chrono>
#include <future>
#include <vector>


class MrinalsControlLoop
{
	public:
	enum class RecordMode{
			FULL_PROFILE,
			SPEED_PROFILE,
			NONE
	};

	enum class PlayMode{
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
	static int ticker;
	static RecordMode rMode;
	static PlayMode pMode;


	private:
	static double kTurn;
	static double kP;
	static double kI;
	static double kD;
	static double kF;

};


#endif /* SRC_MRINALSMrinalsControlLoop_H_ */
