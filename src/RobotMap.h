#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"
#include "AHRS.h"
#include "CANTalon.h"

#define R_DRIVE_1 3
#define R_DRIVE_2 4
#define L_DRIVE_1 1
#define L_DRIVE_2 2
//#define BRAKES_OUT 4
//#define BRAKES_IN 0
#define FLYWHEEL 5


#define INTAKE_ROLLER 0 //Change
#define STORAGE_ROLLER 6
//#define RIGHT_DRIVE_ENC 123123
//#define LEFT_DRIVE_ENC 321321
#define GEAR_DRIVE 987897
//#define GEAR_DRIVE_UP 666

//Pistons
#define PCM_ID 61
#define PTO_PISTON 0
#define SHIFTERS 1
#define LFUEL_GATE 7
#define RFUEL_GATE 6
#define GEAR_PISTON 5
#define SHOOTER_PISTON 4

#define PASSIVE_ACQ 2
//anthony is a pretty fly guy
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;
class RobotMap
{
public:
	static std::shared_ptr<CANTalon> driverDrive1;
	static std::shared_ptr<CANTalon> driverDrive2;
	static std::shared_ptr<CANTalon> drivelDrive1;
	static std::shared_ptr<CANTalon> drivelDrive2;
	static std::shared_ptr<Solenoid> drivebrakes;
	static std::shared_ptr<CANTalon> shooterflywheel;
	static std::shared_ptr<CANTalon> acquisitionintakeRoller;
	static std::shared_ptr<CANTalon> storageballControlMotor;
//	static std::shared_ptr<Encoder> driverEnc;
//	static std::shared_ptr<Encoder> drivelEnc;
	static std::shared_ptr<AHRS> driveahrs;



	static std::shared_ptr<Solenoid> drivegearShift;
	static std::shared_ptr<Solenoid> shooterangleShift;
	static std::shared_ptr<Solenoid> gearpiston;
	static std::shared_ptr<Solenoid> climbingdriveShiftPiston;
	static std::shared_ptr<Solenoid> acquisitionarmPiston;
	static std::shared_ptr<Solenoid> rightGate;
	static std::shared_ptr<Solenoid> leftGate;
	static std::shared_ptr<Solenoid> doorPiston;


	static void init();
private:

};


#endif  // ROBOTMAP_H
