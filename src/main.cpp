#include "task.hpp"
#include <iostream>

int main() {
    Task task(1, "sensor_task");

    std::cout << "Created task: "
          << task.getId()
          << " "
          << task.getName()
          << std::endl;

    task.setState(TaskState::RUNNING);

    if (task.getState() == TaskState::RUNNING) {
        std::cout << "Task is running" << std::endl;
    }

    return 0;
}