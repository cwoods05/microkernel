#pragma once

class Mutex {
public:
    Mutex();

    bool lock();
    void unlock();
    bool isLocked() const;

private:
    bool locked;
};