#include "AutoDriveSpeed.h"
#include "Robot.h"

AutoDriveSpeed::AutoDriveSpeed() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::drive.get());
}

// Called just before this Command runs the first time
void AutoDriveSpeed::Initialize() {
	speed = SmartDashboard::GetNumber("test_setPoint", 0.0);
	Robot::drive->SetControlMode(Drive::DriveControlMode::VelocityDriving);
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveSpeed::Execute() {
	speed = SmartDashboard::GetNumber("test_setPoint", 0.0);
	Robot::drive->TankDrive(speed, speed);
	printf("%d\n",(RobotMap::drivelDrive1->GetEncVel()));

}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveSpeed::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoDriveSpeed::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveSpeed::Interrupted() {

}
