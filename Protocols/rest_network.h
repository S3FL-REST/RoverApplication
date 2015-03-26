#ifndef REST_NETWORK_H
#define REST_NETWORK_H

#include <QString>
#include <QStringList>

#include <QByteArray>

#include <QImage>
#include <QBuffer>
#include <QDataStream>

class Network2Rover
{
public:
    enum run_mode {
      STOP = 0,
      TELEOP = 1,
      SAFE_AUTON = 2,
      FULL_AUTON = 3
    };

    enum linear_actuator {
        L_FORWARD = 0,
        L_STOP = 1,
        L_REVERSE = 2
    };

    Network2Rover();

    static const int NUM_PARAMS = 3;

    void SetLeftJoystick(int);
    void SetRightJoystick(int);
    void SetRunMode(run_mode);

    int GetLeftJoystick() const;
    int GetRightJoystick() const;
    run_mode GetRunMode() const;

    QByteArray ToByteArray() const;
    bool ParseData(QByteArray&);

private:
    int left_joystick;
    int right_joystick;
    run_mode current_mode;
};

class Network2Base
{
public:
    Network2Base();

    void SetImage(QImage&);

    QImage GetImage() const;

    QByteArray ToByteArray() const;
    bool ParseData(QByteArray&);

private:
    QImage image;
};

#endif // REST_NETWORK_H
