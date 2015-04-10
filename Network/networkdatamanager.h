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

    const Network2Rover & GetProtocol() const;

    Network2Rover::run_mode GetCurrentRunMode() const;

    void SetPicture(QImage);
    void SendDataToBase();

    ~NetworkDataManager();

private:
    Network2Rover dataIn;
    Network2Base dataOut;

signals:
    void SendData(QByteArray);

public slots:
    void ResetToDefaults();
    void ParseData(QByteArray);
};

#endif // NETWORKDATAMANAGER_H
