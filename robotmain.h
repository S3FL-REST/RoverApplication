#ifndef ROBOTMAIN_H
#define ROBOTMAIN_H

#include <QObject>

#include <QTimer>
#include <QThread>

#include <QCoreApplication>

#include "Computer/temperaturemonitor.h"

#include "Serial/serialport.h"
#include "Controls/robotdrive.h"

#include "Network/networkserver.h"
#include "Network/networkdatamanager.h"

#include "Protocols/rest_network.h"

#include "Vision/camera.h"

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
    NetworkDataManager networkData;

    Camera frontCam;

    Network2Rover::run_mode runMode;

private slots:
    void MainLoop();
    void VisionLoop();
    void PeriodicLoop();
    void NetworkLoop();
};

#endif // ROBOTMAIN_H
