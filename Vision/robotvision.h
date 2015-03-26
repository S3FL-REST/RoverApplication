#ifndef ROBOTVISION_H
#define ROBOTVISION_H

#include <cmath>

class RobotVision
{
public:
    RobotVision ();

     void SetAngleAndDistance (double, double);
     void SetRobotAngle(double);
     void SetTrackingTarget(bool);

     //Returns theta of robot from dump site
     double GetAngle();

     //Returns distance of robot from dump site
     double GetDistance();

     //Returns angle of robot
     double GetRobotAngle();

     double GetLinearDistance();
     double GetHorizontalDistance();

     bool IsTracking();

     double GetLimitObstacle();
     double GetLimitMining();

     bool IsInObstacleField();
     bool IsInMiningArea();
     bool IsInHomeArea();

 private:
     double angle;
     double distance;
     double robotAngle;

     double isTrackingCamera;

     static const double PI;

     static const double LIMIT_OBSTACLE;
     static const double LIMIT_MINING;
};

#endif // ROBOTVISION_H
