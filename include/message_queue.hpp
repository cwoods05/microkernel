#pragma once

#include <queue>
#include <cstddef>

template <typename T>
class MessageQueue {
public:
    explicit MessageQueue(std::size_t capacity);

    bool send(const T& message);
    bool receive(T& outMessage);

    bool isEmpty() const;
    bool isFull() const;
    std::size_t size() const;

private:
    std::queue<T> queue;
    std::size_t capacity;
};

template <typename T>
MessageQueue<T>::MessageQueue(std::size_t capacity)
    : capacity(capacity) {}

template <typename T>
bool MessageQueue<T>::send(const T& message) {
    if (isFull()) {
        return false;
    }

    queue.push(message);
    return true;
}

template <typename T>
bool MessageQueue<T>::receive(T& outMessage) {
    if (isEmpty()) {
        return false;
    }

    outMessage = queue.front();
    queue.pop();
    return true;
}

template <typename T>
bool MessageQueue<T>::isEmpty() const {
    return queue.empty();
}

template <typename T>
bool MessageQueue<T>::isFull() const {
    return queue.size() >= capacity;
}

template <typename T>
std::size_t MessageQueue<T>::size() const {
    return queue.size();
}