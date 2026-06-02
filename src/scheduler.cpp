#include "scheduler.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

void Scheduler::addTask(const Task& task) {
    tasks.push_back(task);

    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.getPriority() > b.getPriority();
    });
}

void Scheduler::runOnce() {
    for (Task& task : tasks){
        task.updateState();
        if (task.getState() == TaskState::READY) {
            std::cout << "[scheduler] running " << task.getName() 
            << " priority= " << task.getPriority() << std::endl;
            task.run();
        }
    }
}

void Scheduler::start() {
    while (true) {
        runOnce();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}