#include "robotmain.h"

RobotMain::RobotMain(QObject *parent) : QObject(parent),
    mainTimer(this), visionTimer(this), periodicTimer(this), networkTimer(this),
    driveSerialPort("COM4"), drive(this),
    networkData(this)
{
    //Start Drive Serial
    driveSerialPort.moveToThread(&driveSerialThread);
    driveSerialThread.start();

    connect(&driveSerialPort, SIGNAL(DataAvailable(QByteArray)), &drive, SLOT(ReceiveData(QByteArray)));
    connect(&drive, SIGNAL(SendDataSig(QByteArray)), &driveSerialPort, SLOT(TransmitData(QByteArray)));

    //Start Network Thread
    server.moveToThread(&networkThread);
    networkThread.start();

    connect(&server, SIGNAL(DataReceived(QByteArray)), &networkData, SLOT(ParseData(QByteArray)));
    connect(&server, SIGNAL(ConnectionLost()), &networkData, SLOT(ResetToDefaults()));

    //Connect Timers
    mainTimer.setInterval(5);
    connect(&mainTimer, SIGNAL(timeout()), this, SLOT(MainLoop()));

    visionTimer.setInterval(50);
    connect(&visionTimer, SIGNAL(timeout()), this, SLOT(VisionLoop()));

    periodicTimer.setInterval(1000);
    connect(&periodicTimer, SIGNAL(timeout()), this, SLOT(PeriodicLoop()));

    networkTimer.setInterval(500);
    connect(&networkTimer, SIGNAL(timeout()), this, SLOT(NetworkLoop()));
}

void RobotMain::Start() {
    mainTimer.start();
    visionTimer.start();
    periodicTimer.start();
    networkTimer.start();

    qDebug() << "Staring Main Run Loop";
}

void RobotMain::Stop() {
    mainTimer.stop();
    visionTimer.stop();
    periodicTimer.stop();
    networkTimer.stop();

    qDebug() << "Stopping Main Run Loop";
}

void RobotMain::MainLoop() {
    if (networkData.GetCurrentRunMode() == Network2Rover::STOP) {
        drive.SetDriveMotors(0, 0);
    }

    else if (networkData.GetCurrentRunMode() == Network2Rover::TELEOP) {
        int joyL = networkData.GetJoystickLeft();
        int joyR = networkData.GetJoystickRight();

        drive.SetDriveMotors(joyL, joyR);
    }

    else {
        drive.SetDriveMotors(0, 0);
    }
}

void RobotMain::VisionLoop() {

}

void RobotMain::PeriodicLoop() {
    QCoreApplication::quit();
}

void RobotMain::NetworkLoop() {

}

RobotMain::~RobotMain() {

}

