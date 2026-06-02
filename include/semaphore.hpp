#pragma once

class Semaphore {
public:
    explicit Semaphore(int initialCount);

    bool wait();
    void signal();
    int getCount() const;

private:
    int count;
};