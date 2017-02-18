// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "Robot.h"

std::shared_ptr<CANTalon> RobotMap::driverDrive1;
std::shared_ptr<CANTalon> RobotMap::driverDrive2;
std::shared_ptr<CANTalon> RobotMap::drivelDrive1;
std::shared_ptr<CANTalon> RobotMap::drivelDrive2;
std::shared_ptr<Solenoid> RobotMap::drivebrakes;
std::shared_ptr<CANTalon> RobotMap::shooterflywheel;
std::shared_ptr<Solenoid> RobotMap::shooterangleShift;
std::shared_ptr<Solenoid> RobotMap::gearpiston;
std::shared_ptr<Solenoid> RobotMap::climbingdriveShiftPiston;
std::shared_ptr<Solenoid> RobotMap::acquisitionarmPiston;
std::shared_ptr<CANTalon> RobotMap::acquisitionintakeRoller;
std::shared_ptr<CANTalon> RobotMap::storageballControlMotor;
//std::shared_ptr<Encoder> RobotMap::driverEnc;
//std::shared_ptr<Encoder> RobotMap::drivelEnc;
std::shared_ptr<AHRS> RobotMap::driveahrs;
std::shared_ptr<Solenoid> RobotMap::drivegearShift;
std::shared_ptr<Solenoid> RobotMap::rightGate;
std::shared_ptr<Solenoid> RobotMap::leftGate;
std::shared_ptr<Solenoid> RobotMap::doorPiston;

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    LiveWindow *lw = LiveWindow::GetInstance();

    driverDrive1.reset(new CANTalon(R_DRIVE_1));
    lw->AddActuator("Drive", "rDrive1", driverDrive1);
    
    driverDrive2.reset(new CANTalon(R_DRIVE_2));
    lw->AddActuator("Drive", "rDrive2", driverDrive2);
    
    drivelDrive1.reset(new CANTalon(L_DRIVE_1));
    lw->AddActuator("Drive", "lDrive1", drivelDrive1);
    
    drivelDrive2.reset(new CANTalon(L_DRIVE_2));
    lw->AddActuator("Drive", "lDrive2", drivelDrive2);
    
    driverDrive2->SetControlMode(CANTalon::ControlMode::kFollower);
    drivelDrive2->SetControlMode(CANTalon::ControlMode::kFollower);
    driverDrive2->Set(R_DRIVE_1);
    drivelDrive2->Set(L_DRIVE_1);
    
    shooterflywheel.reset(new CANTalon(FLYWHEEL));
    lw->AddActuator("Shooter", "flywheel1", shooterflywheel);

    shooterangleShift.reset(new Solenoid(PCM_ID,SHOOTER_PISTON));
    lw->AddActuator("Shooter", "angleShift", shooterangleShift);

    gearpiston.reset(new Solenoid(PCM_ID,GEAR_PISTON));
    lw->AddActuator("Gear", "piston", gearpiston);

    climbingdriveShiftPiston.reset(new Solenoid(PCM_ID,PTO_PISTON));
    lw->AddActuator("Climbing", "driveShiftPiston", climbingdriveShiftPiston);

    drivegearShift.reset(new Solenoid(PCM_ID,SHIFTERS));
    lw->AddActuator("GearShifting","driveGearShift",drivegearShift);

    leftGate.reset(new Solenoid(PCM_ID,LFUEL_GATE));
    lw->AddActuator("leftGate","leftGate",leftGate);

    rightGate.reset(new Solenoid(PCM_ID,RFUEL_GATE));
    lw->AddActuator("rightGate","rightGate",rightGate);

    doorPiston.reset(new Solenoid(PCM_ID,PASSIVE_ACQ));
    lw->AddActuator("doorPiston","doorPiston",doorPiston);


//    acquisitionarmPiston.reset(new Solenoid());
//    lw->AddActuator("Acquisition", "armPiston", acquisitionarmPiston);
    
    acquisitionintakeRoller.reset(new CANTalon(INTAKE_ROLLER));
    lw->AddActuator("Acquisition", "intakeRoller", acquisitionintakeRoller);
    
    storageballControlMotor.reset(new CANTalon(STORAGE_ROLLER));
    lw->AddActuator("Storage", "ballControlMotor", storageballControlMotor);
    
//    driverEnc.reset(new Encoder();

//    drivelEnc.reset(new Encoder(LEFT_DRIVE_ENC));

    driveahrs.reset(new AHRS(frc::SerialPort::kMXP));

//    drivegearShift.reset(new Solenoid(GEAR_DRIVE_DOWN, GEAR_DRIVE_UP));
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
