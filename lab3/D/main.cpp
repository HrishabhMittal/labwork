#include <iostream>
#include <ostream>
#define ONE_STACK
#include "queue.hpp"

int main() {
    Queue<int,5> q;
    std::cout<<"isEmpty: "<<q.isEmpty()<<std::endl;
    q.enqueue(1);
    std::cout<<q.peek()<<std::endl;
    q.enqueue(2);
    std::cout<<q.peek()<<std::endl;
    q.dequeue();
    std::cout<<q.peek()<<std::endl;
    q.enqueue(3);
    std::cout<<q.peek()<<std::endl;
    q.enqueue(4);
    std::cout<<q.peek()<<std::endl;
    q.dequeue();
    std::cout<<q.peek()<<std::endl;
    q.dequeue();
    std::cout<<q.peek()<<std::endl;
    std::cout<<"isEmpty: "<<q.isEmpty()<<std::endl;
    q.dequeue();
    std::cout<<"isEmpty: "<<q.isEmpty()<<std::endl;
}
