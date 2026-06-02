#include "task.hpp"

Task::Task(int id, const std::string& name, int priority, TaskFunction function)
    : id(id), name(name), priority(priority), state(TaskState::READY), function(function) {}

int Task::getId() const {
    return id;
}

std::string Task::getName() const {
    return name;
}

TaskState Task::getState() const {
    return state;
}

void Task::setState(TaskState newState) {
    state = newState;
}

void Task::run() {
    if (state == TaskState::READY) {
        return;
    }

    state = TaskState::RUNNING;
    function(*this);
    state = TaskState::READY;
}

void Task::sleepFor(int milliseconds) {
    state = TaskState::SLEEPING;
    wakeTime = std::chrono::steady_clock::now()
             + std::chrono::milliseconds(milliseconds);
}

void Task::updateState() {
    if (state == TaskState::SLEEPING &&
        std::chrono::steady_clock::now() >= wakeTime) {
        state = TaskState::READY;
    }
}

int Task::getPriority() const {
    return priority;
}