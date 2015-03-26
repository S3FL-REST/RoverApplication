#include "serialmanager.h"

SerialManager::SerialManager(QObject *parent) : QObject(parent) {

}

void SerialManager::SendData(QByteArray data) {
    emit SendDataSig(data);
}

SerialManager::~SerialManager() {

}

