#include "networkdatamanager.h"

NetworkDataManager::NetworkDataManager(QObject *parent) : QObject(parent) {

}

int NetworkDataManager::GetJoystickLeft() const {
    return dataIn.GetLeftJoystick();
}

int NetworkDataManager::GetJoystickRight() const {
    return dataIn.GetRightJoystick();
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

NetworkDataManager::~NetworkDataManager() {

}

