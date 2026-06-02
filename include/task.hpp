#pragma once // Only include this header once during compilation.
#include <string>

enum class TaskState {
    READY,
    RUNNING,
    FINISHED
};

class Task {
    public:
        Task(int id, const std::string& name);

        int getId() const;
        std::string getName() const;
        TaskState getState() const;
        void setState(TaskState newState);

    private:
        int id;
        std::string name;
        TaskState state;
};