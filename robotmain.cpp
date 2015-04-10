#include "robotmain.h"

RobotMain::RobotMain(QObject *parent) : QObject(parent),
    mainTimer(this), visionTimer(this), periodicTimer(this), networkTimer(this),
    driveSerialPort("/dev/ttyACM1"), drive(this),
    collectionSerialPort("/dev/ttyACM0"), collection(this),
    networkData(this),
    frontCam(0)
{
    //Start Drive Serial
    driveSerialPort.moveToThread(&driveSerialThread);
    driveSerialThread.start();

    connect(&driveSerialPort, SIGNAL(DataAvailable(QByteArray)), &drive, SLOT(ReceiveData(QByteArray)));
    connect(&drive, SIGNAL(SendDataSig(QByteArray)), &driveSerialPort, SLOT(TransmitData(QByteArray)));

    //Start CollectionSerial
    collectionSerialPort.moveToThread(&collectionSerialThread);
    collectionSerialThread.start();

    connect(&collectionSerialPort, SIGNAL(DataAvailable(QByteArray)), &collection, SLOT(ReceiveData(QByteArray)));
    connect(&collection, SIGNAL(SendDataSig(QByteArray)), &collectionSerialPort, SLOT(TransmitData(QByteArray)));

    //Start Network Thread
    server.moveToThread(&networkThread);
    networkThread.start();

    connect(&server, SIGNAL(DataReceived(QByteArray)), &networkData, SLOT(ParseData(QByteArray)));
    connect(&server, SIGNAL(ConnectionLost()), &networkData, SLOT(ResetToDefaults()));
    connect(&networkData, SIGNAL(SendData(QByteArray)), &server, SLOT(SendData(QByteArray)));

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


// Starts All Run Loops
void RobotMain::Start() {
    mainTimer.start();
    visionTimer.start();
    periodicTimer.start();
    networkTimer.start();

    qDebug() << "Staring Main Run Loop";
}

// Stops All Run Loops
void RobotMain::Stop() {
    mainTimer.stop();
    visionTimer.stop();
    periodicTimer.stop();
    networkTimer.stop();

    qDebug() << "Stopping Main Run Loop";
}

// Main Run Loop - Runs once every 5 ms
void RobotMain::MainLoop() {
    if (runMode != networkData.GetCurrentRunMode()) {
        runMode = networkData.GetCurrentRunMode();
        qDebug() << "New Run Mode: " << runMode;
    }

    if (runMode == Network2Rover::STOP) {
        drive.SetDriveMotors(0, 0);
    }

    else if (runMode == Network2Rover::TELEOP) {
        //Robot Drive
        int joyL = networkData.GetProtocol().GetLeftJoystick();
        int joyR = networkData.GetProtocol().GetRightJoystick();

        Network2Rover::linear_actuator suspActuator = networkData.GetProtocol().GetSuspension();

        drive.SetDriveMotors(joyL, joyR);
        drive.SetSuspension(suspActuator);

        //Robot Collection
        int rate = networkData.GetProtocol().GetArmRate();
        Network2Rover::linear_actuator binActuator = networkData.GetProtocol().GetBinActuator();
        Network2Rover::linear_actuator scoopActuator = networkData.GetProtocol().GetScoopActuator();

        collection.SetRate(rate);
        collection.SetBinActuator(binActuator);
        collection.SetScoopActuator(scoopActuator);
    }

    else {
        drive.SetDriveMotors(0, 0);
    }
}

// Periodic Loop - Runs once every 1000 ms
void RobotMain::PeriodicLoop() {

    //Checks temperature and exits program if temperature exceeds critical value
    double currentTemp = TemperatureMonitor::GetTemperature();

    //qDebug() << currentTemp;

    if (currentTemp > TemperatureMonitor::CRITICAL_TEMP) {
        qDebug() << "Shutdown!!!";
        QCoreApplication::exit(1);
    }
}

// Vision Loop - Runs once every 50 ms
void RobotMain::VisionLoop() {
    frontCam.CaptureImage();
}

// Network Loop - Runs once every 500 ms
void RobotMain::NetworkLoop() {
    //Checks for a new image, and sends image if available
    if (frontCam.HasNewImage()) {
        networkData.SetPicture(frontCam.GetCurrentImage());
        networkData.SendDataToBase();
    }
}

RobotMain::~RobotMain() {

}
