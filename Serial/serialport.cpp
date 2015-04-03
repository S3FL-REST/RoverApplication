#include "serialport.h"

SerialPort::SerialPort(QString port_in, QObject *parent) : QObject(parent),
    readTimer(this), serialPort(this), port(port_in) {

    Connect();
}

bool SerialPort::IsOpen() const {
    return serialPort.isOpen();
}

void SerialPort::Connect() {
    serialPort.setPortName(port);
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);

    connect(&readTimer, SIGNAL(timeout()), this, SLOT(CheckRead()));

    readTimer.start(50);
}

void SerialPort::Disconnect() {
    serialPort.close();

    readTimer.stop();
}

void SerialPort::SerialConnect() {
    if (serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Successfully Opened " << port;
    } else {
        qDebug() << "Error opening " << port << ", " << serialPort.errorString();
        this->thread()->msleep(1000);
    }
}

void SerialPort::TransmitData(QByteArray data) {
    serialPort.write(data);
    serialPort.flush();
}

void SerialPort::CheckRead() {
    if (serialPort.isOpen()) {
        if (serialPort.bytesAvailable() <= 0) return;

        QByteArray byteArray;

        while (serialPort.canReadLine())
            byteArray += serialPort.readLine();

        emit DataAvailable(byteArray);
    } else {
        SerialConnect();
    }
}

SerialPort::~SerialPort() {

}

