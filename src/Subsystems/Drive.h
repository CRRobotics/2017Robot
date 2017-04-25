// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef DRIVE_H
#define DRIVE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "AHRS.h"
#define ENC_PULSE_PER_IN 0
#define R_PER_IN 1 / 3.1415926535 / 3.94
/**
 *
 *
 * @author ExampleAuthor
 */
class Drive: public Subsystem {
public:
	Drive();
	void TankDrive(double lSpeed, double rSpeed, bool speedClosed = false);
	enum class DriveControlMode{
		VelocityTurning,
		VelocityDriving,
		Voltage,
		MotionProfile
	};

	bool BothEncodersPresent();
	bool NavXPresent();
	void SetControlMode(DriveControlMode cMode);
	DriveControlMode GetControlMode();
	void ChangeGear(bool high);
	void SetDriveRampRate(double rampRate);
	double GetDriveRampRate();
	bool GetGear();
	void InitDefaultCommand();
	int GetLEncoder();
	int GetREncoder();
	double GetLPosition();
	double GetRPosition();
	double GetYaw();
	void ResetYaw();
	int GetLEncoderRate();
	int GetREncoderRate();
	double GetLSpeed();
	double GetRSpeed();
	void SetPIDF(double kp, double ki, double kd, double kf);
	static double maxSpeed;

private:
	std::shared_ptr<CANTalon> rDrive1;
	std::shared_ptr<CANTalon> rDrive2;
	std::shared_ptr<CANTalon> lDrive1;
	std::shared_ptr<CANTalon> lDrive2;
	std::shared_ptr<Solenoid> gearShift;
	std::shared_ptr<AHRS> ahrs;

	double closedLoopRampRate;
	DriveControlMode currentControlMode;

	double vTurnP = 0.65;
	double vTurnI = 0.01;
	double vTurnD = 0.5;
	double vTurnF = 0.14;
	double vDriveP = 1.4;//0.90;
	double vDriveI = 0.005;
	double vDriveD = 0.0;
	double vDriveF = 0.9;
	double motionP = 0.0;
	double motionI = 0.0;
	double motionD = 0.0;
	double motionF = 0.0;

};




#endif
