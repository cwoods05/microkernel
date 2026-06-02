#include "task.hpp"
#include <iostream>

void sensorTask() {
    std::cout << "Reading fake sensor data" << std::endl;
}

void motorTask() {
    std::cout << "Updating fake motor control" << std::endl;
}

void telemetryTask() {
    std::cout << "Sending fake telemetry" << std::endl;
}

int main() {
    Task sensor(1, "sensor_task", sensorTask);
    Task motor(2, "motor_task", motorTask);
    Task telemetry(3, "telemetry_task", telemetryTask);
    
    sensor.run();
    motor.run();
    telemetry.run();

    return 0;
}