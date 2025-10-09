#pragma once
#include <cstddef>
#include <ostream>
#include <stdexcept>
template<typename T,size_t s>
class Stack {
    T arr[s];
    size_t top=0;
public:
    Stack() {};
    void pushBack(T e) {
        if (top>=s) throw std::runtime_error("stack overflow");
        arr[top++]=e;
    }
    T popBack() {
        if (top==0) throw std::runtime_error("stack underflow");
        return arr[--top];
    }
    T peek() const {
        return arr[top-1];
    }
    bool isEmpty() const {
        return top==0;
    }
    size_t size() const {
        return s;
    }
    size_t len() const {
        return top;
    }
    bool isFull() const {
        return top==s;
    }
    T operator[](size_t ind) const {
        if (ind<0||ind>=top) throw std::runtime_error("index out of range");
        return arr[ind];
    }
    std::ostream& operator<<(std::ostream& out) const {
        out<<"[";
        for (size_t i=0;i<top;i++) {
            out<<arr[i]<<" ";
        }
        out<<"]";
        return out;
    }
};

