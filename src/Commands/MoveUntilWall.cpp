#include "MoveUntilWall.h"

MoveUntilWall::MoveUntilWall(double _distance) : targetDistance(_distance),
						leftDistance(999), rightDistance(999),
						leftEncoder(0), rightEncoder(0){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(driveTrain);
}

// Called just before this Command runs the first time
void MoveUntilWall::Initialize() {
	/*
	driveTrain->EnablePID();
	driveTrain->setPID(1, 0, 0);
	*/
}

// Called repeatedly when this Command is scheduled to run
void MoveUntilWall::Execute() {
	driveTrain->tankDrive(1, 1);
	//driveTrain->tankDrive(1 - leftEncoder + rightEncoder, 1 - rightEncoder + leftEncoder)
	leftDistance = driveTrain->leftUltra();
	rightDistance = driveTrain->rightUltra();
	leftEncoder = driveTrain->leftEncoder();
	rightEncoder = driveTrain->rightEncoder();
	//driveTrain->setSetpoint(targetDistance - leftDistance);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveUntilWall::IsFinished() {
	return targetDistance - leftDistance < fabs(0.05);// or distanceToTravel - rightDistance < fabs(0.05);
}

// Called once after isFinished returns true
void MoveUntilWall::End() {
	driveTrain->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveUntilWall::Interrupted() {
	driveTrain->Stop();
}
