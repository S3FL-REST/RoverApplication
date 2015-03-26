#ifndef ROBOTDRIVE_H
#define ROBOTDRIVE_H

#include "Serial/serialmanager.h"

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

private:
    int currentLeft;
    int currentRight;

public slots:
    virtual void ReceiveData(QByteArray data);
};

#endif // ROBOTDRIVE_H
