#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
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
    T peek() {
        return arr[top-1];
    }
    bool isEmpty() {
        return top==0;
    }
    size_t size() {
        return s;
    }
    size_t len() {
        return top;
    }
    bool isFull() {
        return top==s;
    }
    T operator[](size_t ind) {
        if (ind<0||ind>=top) throw std::runtime_error("index out of range");
        return arr[ind];
    }
    std::ostream& operator<<(std::ostream& out) {
        out<<"[";
        for (size_t i=0;i<top;i++) {
            out<<arr[i]<<" ";
        }
        out<<"]";
        return out;
    }
};

int main() {
    const size_t num=5;
    Stack<std::string,num> s;
    for (int i=0;i<num;i++) {
        std::string e;
        std::cin>>e;
        s.pushBack(e);
    }
    std::cout<<"number reversed are: ";
    while (!s.isEmpty()) {
        std::cout<<s.popBack()<<" ";
    }
    std::cout<<std::endl;
}
