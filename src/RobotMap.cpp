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
#include "CANTalon.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<CANTalon> RobotMap::driverDrive1;
std::shared_ptr<CANTalon> RobotMap::driverDrive2;
std::shared_ptr<CANTalon> RobotMap::drivelDrive1;
std::shared_ptr<CANTalon> RobotMap::drivelDrive2;
std::shared_ptr<Solenoid> RobotMap::drivebrakes;
std::shared_ptr<CANTalon> RobotMap::shooterflywheel1;
std::shared_ptr<CANTalon> RobotMap::shooterflywheel2;
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
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

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

    drivebrakes.reset(new Solenoid(BRAKES_IN, BRAKES_OUT));
    lw->AddActuator("Drive", "brakes", drivebrakes);
    
    shooterflywheel1.reset(new CANTalon(FLYWHEEL_1));
    lw->AddActuator("Shooter", "flywheel1", shooterflywheel1);
    
    shooterflywheel2.reset(new CANTalon(FLYWHEEL_2));
    lw->AddActuator("Shooter", "flywheel2", shooterflywheel2);
    
    shooterangleShift.reset(new Solenoid(ANGLE_SHIFT_DOWN, ANGLE_SHIFT_UP));
    lw->AddActuator("Shooter", "angleShift", shooterangleShift);
    
    gearpiston.reset(new Solenoid(PISTON_DOWN, PISTON_UP));
    lw->AddActuator("Gear", "piston", gearpiston);
    
    climbingdriveShiftPiston.reset(new Solenoid(DRIVE_SHIFT_PISTON_DOWN, DRIVE_SHIFT_PISTON_UP));
    lw->AddActuator("Climbing", "driveShiftPiston", climbingdriveShiftPiston);
    
    acquisitionarmPiston.reset(new Solenoid(ACQ_ARM_PISTON_DOWN, ACQ_ARM_PISTON_UP));
    lw->AddActuator("Acquisition", "armPiston", acquisitionarmPiston);
    
    acquisitionintakeRoller.reset(new CANTalon(INTAKE_ROLLER));
    lw->AddActuator("Acquisition", "intakeRoller", acquisitionintakeRoller);
    
    storageballControlMotor.reset(new CANTalon(STORAGE_ROLLER));
    lw->AddActuator("Storage", "ballControlMotor", storageballControlMotor);
    
//    driverEnc.reset(new Encoder();

//    drivelEnc.reset(new Encoder(LEFT_DRIVE_ENC));

    driveahrs.reset(new AHRS(frc::SerialPort::kMXP));

    drivegearShift.reset(new Solenoid(GEAR_DRIVE_DOWN, GEAR_DRIVE_UP));
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
