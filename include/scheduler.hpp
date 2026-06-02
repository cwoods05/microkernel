#pragma once

#include "task.hpp"
#include <vector>

class Scheduler {
    public:
        void addTask(const Task& task);

    private:
        std::vector<Task> tasks;
};