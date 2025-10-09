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
    T peek() {
        return arr[l%S];
    }
    bool isEmpty() {
        return h==l;
    }
    bool isFull() {
        return h-l==S;
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

int main() {
    queue<int,5> q;
    q.enqueue(1);
    std::cout<<q<<std::endl;
    q.enqueue(2);
    std::cout<<q<<std::endl;
    q.enqueue(3);
    std::cout<<q<<std::endl;
    q.enqueue(4);
    std::cout<<q<<std::endl;
    q.enqueue(5);
    std::cout<<q<<std::endl;
    q.dequeue();
    q.enqueue(5);
    std::cout<<q<<std::endl;
    q.dequeue();
    std::cout<<q<<std::endl;
    q.dequeue();
    std::cout<<q<<std::endl;
    q.dequeue();
    std::cout<<q<<std::endl;
    q.dequeue();
    std::cout<<q<<std::endl;
    q.dequeue();
    std::cout<<q<<std::endl;
}
