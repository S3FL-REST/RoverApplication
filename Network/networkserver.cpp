#include "networkserver.h"

NetworkServer::NetworkServer(QObject *parent) : QObject(parent), server(this), socket(0) {
    bool listening = server.listen(QHostAddress::Any, PORT);

    if (!listening) qDebug() << "Server Failed to Start";

    connect(&server, SIGNAL(newConnection()), this, SLOT(NewConnection()));
}

bool NetworkServer::IsConnected() {
    return socket != 0 && socket->isOpen();
}

void NetworkServer::NewConnection() {
    if (socket != 0) {
        qDebug() << "Disconnecting Old Socket";

        socket->disconnectFromHost();
        socket->close();

        delete socket;
        socket = 0;
    }

    socket = server.nextPendingConnection();

    qDebug() << "Accepted Connection from " << socket->localAddress().toString();

    connect(socket, SIGNAL(readyRead()), this, SLOT(DataReady()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(SocketDisconnected()));
}

void NetworkServer::SocketDisconnected() {
    qDebug() << "Socket " << socket->localAddress().toString() << " disconnected";

    socket->close();
    disconnect(socket);

    delete socket;
    socket = 0;

    emit ConnectionLost();
}

void NetworkServer::SendData(QByteArray data) {
    if (IsConnected()) {
        socket->write(data);
        socket->flush();
    }
}

void NetworkServer::DataReady() {
    QByteArray data = "";

    while (socket->bytesAvailable())
        data += socket->readAll();

    emit DataReceived(data);
}

NetworkServer::~NetworkServer() {
    disconnect(&server);

    server.close();

    if (socket != 0) socket->close();
    delete socket;
}

