#include "robotvision.h"

//Measurements in Meters

const double RobotVision::PI = 3.1415926;

const double RobotVision::LIMIT_OBSTACLE = 1.5;
const double RobotVision::LIMIT_MINING = 2.94;

RobotVision::RobotVision() : angle (0.0), distance (0.0), robotAngle(0.0), isTrackingCamera(false) {
    //Empty Constructor
}

void RobotVision::SetAngleAndDistance(double a, double d) {
    angle = a;
    distance = d;
}

void RobotVision::SetRobotAngle(double a) {
    robotAngle = a;
}

void RobotVision::SetTrackingTarget(bool tracking) {
    isTrackingCamera = tracking;
}

double RobotVision::GetAngle() {
    return angle;
}

double RobotVision::GetDistance() {
    return distance;
}

double RobotVision::GetRobotAngle() {
    return robotAngle;
}

double RobotVision::GetLinearDistance() {
    return distance * cos(angle * PI / 180.0);
}

double RobotVision::GetHorizontalDistance() {
    return distance * sin(angle * PI / 180.0);
}

bool RobotVision::IsTracking() {
    return isTrackingCamera;
}

double RobotVision::GetLimitObstacle() {
    return LIMIT_OBSTACLE;
}

double RobotVision::GetLimitMining() {
    return LIMIT_MINING;
}

bool RobotVision::IsInObstacleField() {
    return (GetLinearDistance() < LIMIT_MINING && GetLinearDistance() > LIMIT_OBSTACLE);
}

bool RobotVision::IsInMiningArea() {
    return GetLinearDistance() > LIMIT_MINING;
}

bool RobotVision::IsInHomeArea() {
    return GetLinearDistance() < LIMIT_OBSTACLE;
}
