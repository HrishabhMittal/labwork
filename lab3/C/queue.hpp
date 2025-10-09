#pragma once
#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
template<typename T,size_t S>
class queue {
    T arr[S];
    size_t l=0,h=0;
public:
    void enqueue(const T& x) {
        if (h-l>=S) throw std::runtime_error("queue full"); 
        arr[(h++)%S]=x;
    }
    void dequeue() {
        if (l==h) throw std::runtime_error("queue empty");
        l++;
        if (l>=S) {
            l%=S;
            h%=S;
        }
    }
    T peek() const {
        return arr[l%S];
    }
    bool isEmpty() const {
        return h==l;
    }
    bool isFull() const {
        return h-l==S;
    }
    size_t size() const {
        return h - l;
    }
    friend std::ostream& operator<<(std::ostream& out,const queue<T,S>& q) {
        std::cout<<"[ ";
        for (size_t s=q.l;s<q.h;s++) {
            std::cout<<q.arr[s%S]<<" ";
        }
        std::cout<<"]";
        return out;
    }
};

