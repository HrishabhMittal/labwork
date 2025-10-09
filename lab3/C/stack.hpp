#pragma once

#include "queue.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T, size_t S>
class Stack {
private:
#ifdef ONE_QUEUE
    queue<T, S> q;
#else
    queue<T, S> q1, q2;
#endif

public:
    void push(const T& x) {
#ifdef ONE_QUEUE
        q.enqueue(x);
        size_t n = q.size();
        for (size_t i=0;i<n-1;i++) {
            T tmp = q.peek();
            q.dequeue();
            q.enqueue(tmp);
        }
#else
        q2.enqueue(x);
        while (!q1.isEmpty()) {
            T tmp = q1.peek();
            q1.dequeue();
            q2.enqueue(tmp);
        }
        std::swap(q1, q2);
#endif
    }

    void pop() {
#ifdef ONE_QUEUE
        if (q.isEmpty()) throw std::runtime_error("Stack empty");
        q.dequeue();
#else
        if (q1.isEmpty()) throw std::runtime_error("Stack empty");
        q1.dequeue();
#endif
    }

    T peek() const {
#ifdef ONE_QUEUE
        if (q.isEmpty()) throw std::runtime_error("Stack empty");
        return q.peek();
#else
        if (q1.isEmpty()) throw std::runtime_error("Stack empty");
        return q1.peek();
#endif
    }

    bool isEmpty() const {
#ifdef ONE_QUEUE
        return q.isEmpty();
#else
        return q1.isEmpty();
#endif
    }
};
