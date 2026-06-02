#include "scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void Scheduler::addTask(const Task& task) {
    tasks.push_back(task);
}

void Scheduler::runOnce() {
    for (Task& task : tasks){
        if (task.getState() == TaskState::READY) {
            std::cout << "[scheduler] running " << task.getName() << std::endl;
            task.run();
        }
    }
}

void Scheduler::start() {
    while (true) {
        runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}