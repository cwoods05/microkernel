#pragma once // Only include this header once during compilation.
#include <string>
#include <functional>
#include <chrono>

//forward declaration
class Task;

// A function that takes no arguments and returns void.
// just a alias so we don't keep rewriting
using TaskFunction = std::function<void(Task&)>;

enum class TaskState {
    READY,
    RUNNING,
    FINISHED,
    SLEEPING
};

class Task {
    public:
        Task(int id, const std::string& name, int priority, TaskFunction function);

        int getId() const;
        std::string getName() const;
        TaskState getState() const;
        void setState(TaskState newState);
        void run();
        void sleepFor(int milliseconds);
        void updateState();
        int getPriority() const;

    private:
        int id;
        std::string name;
        TaskState state;
        TaskFunction function;
        std::chrono::steady_clock::time_point wakeTime;
        int priority;
};