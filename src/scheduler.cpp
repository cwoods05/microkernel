#include "scheduler.hpp"

void Scheduler::addTask(const Task& task) {
    tasks.push_back(task);
}