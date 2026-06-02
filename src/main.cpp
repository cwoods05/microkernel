#include "scheduler.hpp"
#include "task.hpp" 
#include <iostream>
#include "mutex.hpp"
#include "semaphore.hpp"
#include "message_queue.hpp"

int sharedCounter = 0;
Mutex counterMutex;

int sensorBuffer = 0;
Semaphore dataAvailable(0);
Mutex bufferMutex;

struct ImuMessage {
    int sequence;
    double pitch;
    double yaw;
};

struct MotorCommand {
    int sequence;
    double leftSpeed;
    double rightSpeed;
};

MessageQueue<ImuMessage> imuQueue(5);
MessageQueue<MotorCommand> motorQueue(5);

int imuSequence = 0;
int commandSequence = 0;

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

void counterTaskA(Task& self) {
    if (counterMutex.lock()) {
        int local = sharedCounter;
        local++;
        sharedCounter = local;

        std::cout << "[counter A] sharedCounter=" << sharedCounter << std::endl;
        counterMutex.unlock();
    }

    self.sleepFor(300);
}

void counterTaskB(Task& self) {
    if (counterMutex.lock()) {
        int local = sharedCounter;
        local++;
        sharedCounter = local;

        std::cout << "[counter B] sharedCounter=" << sharedCounter << std::endl;
        counterMutex.unlock();
    }

    self.sleepFor(300);
}

void producerTask(Task& self) {
    if (bufferMutex.lock()) {
        sensorBuffer++;
        std::cout << "[producer] produced data=" << sensorBuffer << std::endl;
        bufferMutex.unlock();

        dataAvailable.signal();
    }

    self.sleepFor(400);
}

void consumerTask(Task& self) {
    if (dataAvailable.wait()) {
        if (bufferMutex.lock()) {
            std::cout << "[consumer] consumed data=" << sensorBuffer << std::endl;
            bufferMutex.unlock();
        }
    } else {
        std::cout << "[consumer] no data available" << std::endl;
    }

    self.sleepFor(200);
}

void imuTask(Task& self) {
    ImuMessage msg {
        imuSequence++,
        1.5,
        -0.7
    };

    if (imuQueue.send(msg)) {
        std::cout << "[imu] produced packet seq="
                  << msg.sequence
                  << " pitch="
                  << msg.pitch
                  << " yaw="
                  << msg.yaw
                  << std::endl;
    } else {
        std::cout << "[imu] queue full, dropped packet" << std::endl;
    }

    self.sleepFor(100);
}

void controlTask(Task& self) {
    ImuMessage imu;

    if (imuQueue.receive(imu)) {
        MotorCommand cmd {
            commandSequence++,
            0.5 + imu.pitch * 0.01,
            0.5 - imu.yaw * 0.01
        };

        if (motorQueue.send(cmd)) {
            std::cout << "[control] consumed imu seq="
                      << imu.sequence
                      << " produced motor cmd seq="
                      << cmd.sequence
                      << std::endl;
        } else {
            std::cout << "[control] motor queue full, command dropped" << std::endl;
        }
    } else {
        std::cout << "[control] no imu data available" << std::endl;
    }

    self.sleepFor(50);
}

void roverTelemetryTask(Task& self) {
    MotorCommand cmd;

    if (motorQueue.receive(cmd)) {
        std::cout << "[telemetry] motor cmd seq="
                  << cmd.sequence
                  << " left="
                  << cmd.leftSpeed
                  << " right="
                  << cmd.rightSpeed
                  << std::endl;
    } else {
        std::cout << "[telemetry] no motor command available" << std::endl;
    }

    self.sleepFor(250);
}

int main() {
    Task sensor(1, "sensor_task", 2, sensorTask);
    Task motor(2, "motor_task", 0, motorTask);
    Task telemetry(3, "telemetry_task", 4, telemetryTask);
    Task watchdog(4, "watchdog_task", 1, watchdogTask);
    Task counterA(5, "counter_task_a", 3, counterTaskA);
    Task counterB(6, "counter_task_b", 3, counterTaskB);
    Task producer(7, "producer_task", 2, producerTask);
    Task consumer(8, "consumer_task", 2, consumerTask);
    Task imu(9, "imu_task", 1, imuTask);
    Task control(10, "control_task", 0, controlTask);
    Task roverTelemetry(11, "rover_telemetry_task", 3, roverTelemetryTask);
    Scheduler scheduler;

    scheduler.addTask(sensor);
    scheduler.addTask(motor);
    scheduler.addTask(telemetry);
    scheduler.addTask(watchdog);
    scheduler.addTask(counterA);
    scheduler.addTask(counterB);
    scheduler.addTask(producer);
    scheduler.addTask(consumer);
    scheduler.addTask(imu);
    scheduler.addTask(control);
    scheduler.addTask(roverTelemetry);
    scheduler.start();

    return 0;
}