#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QObject>

#include <QByteArray>

class SerialManager : public QObject
{
    Q_OBJECT
public:
    explicit SerialManager(QObject *parent = 0);
    ~SerialManager();

protected:
    void SendData(QByteArray data);

signals:
    void SendDataSig(QByteArray);

public slots:

    virtual void ReceiveData(QByteArray) = 0;
};

#endif // SERIALMANAGER_H
