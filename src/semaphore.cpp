#include "semaphore.hpp"

Semaphore::Semaphore(int initialCount)
    : count(initialCount) {}

bool Semaphore::wait() {
    if (count <= 0) {
        return false;
    }

    count--;
    return true;
}

void Semaphore::signal() {
    count++;
}

int Semaphore::getCount() const {
    return count;
}