#ifndef TEMPERATUREMONITOR_H
#define TEMPERATUREMONITOR_H

#include <fstream>

using namespace std;

class TemperatureMonitor {

public:
    static float GetTemperature();

    static const float CRITICAL_TEMP = 85.0;
};

#endif // TEMPERATUREMONITOR_H
