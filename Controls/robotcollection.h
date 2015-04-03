#ifndef ROBOTCOLLECTION_H
#define ROBOTCOLLECTION_H

#include "Serial/serialmanager.h"
#include "Protocols/rest_network.h"

#include <QObject>
#include <QByteArray>

#include <QDebug>

class RobotCollection : public SerialManager
{
public:
    RobotCollection(QObject *parent = 0);
    ~RobotCollection();

    void SetRate(int r);
    void SetBinActuator(Network2Rover::linear_actuator l_dir);
    void SetScoopActuator(Network2Rover::linear_actuator l_dir);

private:
    int armRate;
    Network2Rover::linear_actuator binActuator;
    Network2Rover::linear_actuator scoopActuator;

public slots:
    virtual void ReceiveData(QByteArray data);
};

#endif // ROBOTCOLLECTION_H
