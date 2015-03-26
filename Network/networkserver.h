#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QObject>

#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>

#include <QDebug>

class NetworkServer : public QObject
{
    Q_OBJECT
public:
    explicit NetworkServer(QObject *parent = 0);

    bool IsConnected();

    ~NetworkServer();

private:
    QTcpServer server;
    QTcpSocket *socket;

    static const int PORT = 3141;

signals:
    void DataReceived(QByteArray);
    void ConnectionLost();

public slots:
    void NewConnection();
    void SendData(QByteArray);

private slots:
    void SocketDisconnected();
    void DataReady();
};

#endif // NETWORKSERVER_H
