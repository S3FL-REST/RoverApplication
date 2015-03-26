#ifndef NETWORKDATAMANAGER_H
#define NETWORKDATAMANAGER_H

#include <QObject>
#include <QByteArray>

#include "Protocols/rest_network.h"

#include <QDebug>

class NetworkDataManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkDataManager(QObject *parent = 0);

    int GetJoystickLeft() const;
    int GetJoystickRight() const;
    Network2Rover::run_mode GetCurrentRunMode() const;

    ~NetworkDataManager();

private:
    Network2Rover dataIn;

signals:

public slots:
    void ResetToDefaults();
    void ParseData(QByteArray);
};

#endif // NETWORKDATAMANAGER_H
