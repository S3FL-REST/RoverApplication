#include "robotcollection.h"

RobotCollection::RobotCollection(QObject *parent)
    : SerialManager(parent),
        armRate(0),
        binActuator(Network2Rover::L_STOP), scoopActuator(Network2Rover::L_STOP) {
    //Empty Constructor
}

void RobotCollection::ReceiveData(QByteArray data) {
    //qDebug() << QString(data);
}

void RobotCollection::SetRate(int r) {
    if (r != armRate) {
        QString dataOut = QString("a:%1\n").arg(r);
        armRate = r;

        emit SendData(dataOut.toUtf8());

        qDebug() << "Setting arm rate to " << r;
    }
}

void RobotCollection::SetBinActuator(Network2Rover::linear_actuator l_dir) {
    if (l_dir != binActuator) {
        QString dataOut = QString("b:%1\n").arg(static_cast<int>(l_dir));
        binActuator = l_dir;

        emit SendData(dataOut.toUtf8());

        switch (l_dir) {
        case Network2Rover::L_STOP:
            qDebug() << "Stopping bin actuator";
            break;
        case Network2Rover::L_FORWARD:
            qDebug() << "Extending bin actuator";
            break;
        case Network2Rover::L_REVERSE:
            qDebug() << "Retracting bin actuator";
            break;
        default:
            qDebug() << "Error with bin actuator!";
        }
    }
}

void RobotCollection::SetScoopActuator(Network2Rover::linear_actuator l_dir) {
    if (l_dir != scoopActuator) {
        QString dataOut = QString("b:%1\n").arg(static_cast<int>(l_dir));
        scoopActuator = l_dir;

        emit SendData(dataOut.toUtf8());

        switch (l_dir) {
        case Network2Rover::L_STOP:
            qDebug() << "Stopping scoop actuator";
            break;
        case Network2Rover::L_FORWARD:
            qDebug() << "Extending scoop actuator";
            break;
        case Network2Rover::L_REVERSE:
            qDebug() << "Retracting scoop actuator";
            break;
        default:
            qDebug() << "Error with scoop actuator!";
        }
    }
}

RobotCollection::~RobotCollection() {

}

