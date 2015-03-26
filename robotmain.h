#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H

#include <QObject>

#include <QTimer>
#include <QThread>

#include "Serial/serialport.h"
#include "Controls/robotdrive.h"

#include "Network/networkserver.h"

class RobotMain : public QObject
{
    Q_OBJECT
public:
    explicit RobotMain(QObject *parent = 0);
    ~RobotMain();

    void Start();
    void Stop();

private:
    QTimer mainTimer;
    QTimer visionTimer;
    QTimer periodicTimer;
    QTimer networkTimer;

    QThread driveSerialThread;
    SerialPort driveSerialPort;
    RobotDrive drive;

    QThread networkThread;
    NetworkServer server;


private slots:
    void MainLoop();
    void VisionLoop();
    void PeriodicLoop();
    void NetworkLoop();
};

#endif // ROBOTMAIN_H
