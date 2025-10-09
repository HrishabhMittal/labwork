#include <cstddef>
#include <iostream>
#include <ostream>
#include <stdexcept>
template<typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(T data=0, Node* next=nullptr): data(data), next(next) {}
};
template<typename T>
class queue {
    Node<T>* head=nullptr,*tail=nullptr;
    size_t l=0,h=0;
public:
    void enqueue(const T& x) {
        if (head==nullptr&&tail==nullptr) {
            head=new Node<T>(x);
            tail=head;
        } else {
            tail->next=new Node<T>(x);
            tail=tail->next;
        }
    }
    void dequeue() {
        if (head==nullptr&&tail==nullptr) throw std::runtime_error("queue empty");
        auto temp=head;
        head=head->next;
        delete temp;
    }
    T peek() {
        return head->data;
    }
    bool isEmpty() {
        return head==nullptr;
    }
    friend std::ostream& operator<<(std::ostream& out,const queue<T>& q) {
        auto dummy=q.head;
        std::cout<<"[ ";
        while (dummy!=nullptr) {
            std::cout<<dummy->data<<" ";
            dummy=dummy->next;
        }
        std::cout<<"]";
        return out;
    }
};


int main() {
    queue<int> q;
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
