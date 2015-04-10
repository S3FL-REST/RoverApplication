#include "networkdatamanager.h"

NetworkDataManager::NetworkDataManager(QObject *parent) : QObject(parent) {

}

const Network2Rover & NetworkDataManager::GetProtocol() const {
    return dataIn;
}

Network2Rover::run_mode NetworkDataManager::GetCurrentRunMode() const {
    return dataIn.GetRunMode();
}

void NetworkDataManager::ParseData(QByteArray data) {
    dataIn.ParseData(data);
}

void NetworkDataManager::ResetToDefaults() {
    if (GetCurrentRunMode() != Network2Rover::FULL_AUTON) {
        dataIn.SetRunMode(Network2Rover::STOP);
        dataIn.SetLeftJoystick(0);
        dataIn.SetRightJoystick(0);
    }
}

void NetworkDataManager::SetPicture(QImage image) {
    dataOut.SetImage(image);
}

void NetworkDataManager::SendDataToBase() {
    emit SendData(dataOut.ToByteArray());
}

NetworkDataManager::~NetworkDataManager() {

}

