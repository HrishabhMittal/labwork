
// queue.hpp
#pragma once

#include "stack.hpp"
#include <stdexcept>

template<typename T, size_t S>
class Queue {
public:
    void enqueue(const T &x) {
        if (in.len() + out.len() >= S) throw std::runtime_error("queue full");
        in.pushBack(x);
    }

    void dequeue() {
        if (!out.isEmpty()) {
            out.popBack();
            return;
        }
        shiftStacks();
        if (out.isEmpty()) throw std::runtime_error("queue empty");
        out.popBack();
    }

    T peek() {
        if (!out.isEmpty()) {
            return out.peek();
        }
        shiftStacks();
        if (out.isEmpty()) throw std::runtime_error("queue empty");
        return out.peek();
    }

    bool isEmpty() const {
        return in.isEmpty() && out.isEmpty();
    }

    bool isFull() const {
        return (in.len() + out.len()) == S;
    }

private:
    Stack<T, S> in, out;
    void shiftStacks() {
        if (out.isEmpty()) {
            while (!in.isEmpty()) {
                out.pushBack(in.popBack());
            }
        }
    }
};
