#include <QCoreApplication>

#include "robotmain.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    RobotMain robotMain;
    robotMain.Start();

    int retVal = a.exec();

    robotMain.Stop();

    return retVal;
}
