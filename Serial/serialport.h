#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>

#include <QtSerialPort/QSerialPort>

#include <QByteArray>
#include <QString>
#include <QTimer>

#include <QThread>

#include <QDebug>

class SerialPort : public QObject
{
    Q_OBJECT

    QTimer readTimer;
    QSerialPort serialPort;

    QString port;

public:
    explicit SerialPort(QString port_in, QObject *parent = 0);
    ~SerialPort();

private:
    void SerialConnect();

signals:
    void DataAvailable(QByteArray);

public slots:
    void TransmitData(QByteArray);
    void Connect();
    void Disconnect();

private slots:
    void CheckRead();
};

#endif // SERIALPORT_H
