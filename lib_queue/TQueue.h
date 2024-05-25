#ifndef LIB_QUEUE_TQUEUE_H_
#define LIB_QUEUE_TQUEUE_H_

#include <queue>
#include <stdexcept>

template <typename T>
class TQueue {
private:
    std::queue<T> q;

public:
    TQueue() = default;

    explicit TQueue(const std::queue<T>& queue) : q(queue) {}

    void push(const T& value) {
        q.push(value);
    }

    void pop() {
        if (q.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        q.pop();
    }

    T& front() {
        if (q.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return q.front();
    }

    const T& front() const {
        if (q.empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return q.front();
    }

    bool isEmpty() const {
        return q.empty();
    }

    int getSize() const {
        return q.size();
    }
};

#endif  // LIB_QUEUE_TQUEUE_H_
