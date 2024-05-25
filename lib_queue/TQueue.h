// Copyright 2024 Dudchenko Olesya

#ifndef LIB_QUEUE_TQUEUE_H_
#define LIB_QUEUE_TQUEUE_H_

#include <iostream>

template <typename T>
class TQueue {
public:
    TQueue(int size = 10) : size(size), front(0), back(0), count(0) {
        data = new T[size];
    }

    ~TQueue() {
        delete[] data;
    }

    void push(const T& value) {
        if (count == size) {
            throw std::overflow_error("Queue is full");
        }
        data[back] = value;
        back = (back + 1) % size;
        ++count;
    }

    T pop() {
        if (count == 0) {
            throw std::underflow_error("Queue is empty");
        }
        T value = data[front];
        front = (front + 1) % size;
        --count;
        return value;
    }

    T front() const {
        if (count == 0) {
            throw std::underflow_error("Queue is empty");
        }
        return data[front];
    }

    bool isEmpty() const {
        return count == 0;
    }

    int getSize() const {
        return count;
    }

private:
    T* data;
    int size;
    int front;
    int back;
    int count;
};

#endif  // LIB_QUEUE_TQUEUE_H_
