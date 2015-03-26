#include "robotmain.h"

RobotMain::RobotMain(QObject *parent) : QObject(parent),
    mainTimer(this), visionTimer(this), periodicTimer(this), networkTimer(this),
    driveSerialPort("COM4"), drive(this)
{
    //Start Drive Serial
    driveSerialPort.moveToThread(&driveSerialThread);
    driveSerialThread.start();

    connect(&driveSerialPort, SIGNAL(DataAvailable(QByteArray)), &drive, SLOT(ReceiveData(QByteArray)));
    connect(&drive, SIGNAL(SendDataSig(QByteArray)), &driveSerialPort, SLOT(TransmitData(QByteArray)));

    //Start Network Thread
    server.moveToThread(&networkThread);
    networkThread.start();
}

void RobotMain::Start() {

}

void RobotMain::Stop() {

}

void RobotMain::MainLoop() {

}

void RobotMain::VisionLoop() {

}

void RobotMain::PeriodicLoop() {

}

void RobotMain::NetworkLoop() {

}

RobotMain::~RobotMain() {

}

