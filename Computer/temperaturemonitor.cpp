#include "temperaturemonitor.h"

//Temperature Filepath: /sys/class/thermal/thermal_zone2/temp

float TemperatureMonitor::GetTemperature() {
    char filename[] = "/sys/class/thermal/thermal_zone2/temp";

    ifstream temp_in(filename);

    if (temp_in.is_open()) {
        float temp;
        temp_in >> temp;
        temp /= 1000.0;

        return temp;
    } else {
        return 0.0;
    }
}
