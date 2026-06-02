#include "scheduler.hpp"
#include "task.hpp" 
#include <iostream>

void sensorTask(Task& self) {
    std::cout << "Reading fake sensor data" << std::endl;
    self.sleepFor(500);
}

void motorTask(Task& self) {
    std::cout << "Updating fake motor control" << std::endl;
    self.sleepFor(100);
}

void telemetryTask(Task& self) {
    std::cout << "Sending fake telemetry" << std::endl;
    self.sleepFor(1000);
}

void watchdogTask(Task& self) {
    std::cout << "Watchdog system health check" << std::endl;
    self.sleepFor(250);
}

int main() {
    Task sensor(1, "sensor_task", 2, sensorTask);
    Task motor(2, "motor_task", 0, motorTask);
    Task telemetry(3, "telemetry_task", 4, telemetryTask);
    Task watchdog(4, "watchdog_task", 1, watchdogTask);
    Scheduler scheduler;

    scheduler.addTask(sensor);
    scheduler.addTask(motor);
    scheduler.addTask(telemetry);
    scheduler.addTask(watchdog);
    scheduler.start();

    return 0;
}