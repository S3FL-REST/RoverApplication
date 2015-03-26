#include "robotdrive.h"

RobotDrive::RobotDrive(QObject *parent) : SerialManager(parent), currentLeft(0), currentRight(0)
{

}

void RobotDrive::ReceiveData(QByteArray data) {
    qDebug() << QString(data);
}

void RobotDrive::SetDriveMotors(int left, int right) {
    if (currentLeft != left || currentRight != right) {
        QString dataOut = QString("d:%1:%2\n\r").arg(left).arg(right);
        emit SendData(dataOut.toUtf8());
        qDebug() << "Setting L:R to " << left << ":" << right;

        currentLeft = left;
        currentRight = right;
    }
}

RobotDrive::~RobotDrive() {

}

