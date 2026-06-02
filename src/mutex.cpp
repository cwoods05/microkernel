#include "mutex.hpp"

Mutex::Mutex()
    : locked(false) {}

bool Mutex::lock() {
    if (locked) {
        return false;
    }

    locked = true;
    return true;
}

void Mutex::unlock() {
    locked = false;
}

bool Mutex::isLocked() const {
    return locked;
}