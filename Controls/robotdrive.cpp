#include "robotdrive.h"

RobotDrive::RobotDrive(QObject *parent) : SerialManager(parent), currentLeft(0), currentRight(0), currentSuspension(Network2Rover::L_STOP)
{
    //Empty Implementation
}

void RobotDrive::ReceiveData(QByteArray data) {
    //qDebug() << QString(data);
}

void RobotDrive::SetDriveMotors(int left, int right) {
    if (currentLeft != left || currentRight != right) {
        QString dataOut = QString("d:%1:%2\n").arg(left).arg(right);

        emit SendData(dataOut.toUtf8());

        currentLeft = left;
        currentRight = right;

        qDebug() << "Setting L:R to " << left << ":" << right;
    }
}

void RobotDrive::SetSuspension(Network2Rover::linear_actuator suspension) {
    if (currentSuspension != suspension) {
        QString dataOut = QString("s:%q\n").arg(static_cast<int>(suspension));
        emit SendData(dataOut.toUtf8());

        currentSuspension = suspension;

        qDebug() << "Setting suspension to " << static_cast<int>(suspension);
    }
}

RobotDrive::~RobotDrive() {

}

