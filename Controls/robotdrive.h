#ifndef ROBOTDRIVE_H
#define ROBOTDRIVE_H

#include "Serial/serialmanager.h"

#include "Protocols/rest_network.h"

#include <QObject>
#include <QByteArray>

#include <QDebug>

class RobotDrive : public SerialManager
{
    Q_OBJECT
public:
    RobotDrive(QObject *parent = 0);
    ~RobotDrive();

    void SetDriveMotors(int left, int right);
    void SetSuspension(Network2Rover::linear_actuator suspension);

private:
    int currentLeft;
    int currentRight;
    Network2Rover::linear_actuator currentSuspension;

public slots:
    virtual void ReceiveData(QByteArray data);
};

#endif // ROBOTDRIVE_H
