#pragma once // Only include this header once during compilation.
#include <string>
#include <functional>
// A function that takes no arguments and returns void.
// just a alias so we don't keep rewriting
using TaskFunction = std::function<void()>; 

enum class TaskState {
    READY,
    RUNNING,
    FINISHED
};

class Task {
    public:
        Task(int id, const std::string& name, TaskFunction function);

        int getId() const;
        std::string getName() const;
        TaskState getState() const;
        void setState(TaskState newState);
        void run();

    private:
        int id;
        std::string name;
        TaskState state;
        TaskFunction function;
};