#include "task.hpp"

Task::Task(int id, const std::string& name, TaskFunction function)
    : id(id), name(name), state(TaskState::READY), function(function) {}

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
    function();
    state = TaskState::READY;
}