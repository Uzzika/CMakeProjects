// Copyright 2024 Dudchenko Olesya

#ifndef LIB_STACK_STACK_H_
#define LIB_STACK_STACK_H_

#include <algorithm>
#include <iostream>

template <typename T>
class Stack {
public:
    explicit Stack(int size = 10) : size(size), top(-1) {
        data = new T[size];
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& value) {
        if (top == size - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data[++top] = value;
    }

    T pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top--];
    }

    T peek() const {
        if (top == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top];
    }

    bool isEmpty() const {
        return top == -1;
    }

private:
    T* data;
    int size;
    int top;
};

template <typename T>
class TDynamicStack {
public:
    TDynamicStack() : data(nullptr), size(0), capacity(0) {}

    void push(const T& value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    T pop() {
        if (size == 0) {
            throw std::underflow_error("Stack underflow");
        }
        return data[--size];
    }

    T peek() const {
        if (size == 0) {
            throw std::underflow_error("Stack underflow");
        }
        return data[size - 1];
    }

    bool isEmpty() const {
        return size == 0;
    }

private:
    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[capacity];
        std::copy(data, data + size, newData);
        delete[] data;
        data = newData;
    }

    T* data;
    int size;
    int capacity;
};

#endif  // LIB_STACK_STACK_H_
