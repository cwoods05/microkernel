#include "task.hpp"

Task::Task(int id, const std::string& name)
    : id(id), name(name), state(TaskState::READY) {}

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