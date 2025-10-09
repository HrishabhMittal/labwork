#include "doubly_linkedlist.hpp"
 

namespace  DoublyLinkedList {
    // O(1)
    bool DoublyLinkedList::isEmpty() const {
        return head==nullptr;
    }
    
    // O(n)
    size_t DoublyLinkedList::count() const {
        size_t cnt=0;
        for (Node* cur=head;cur;cur=cur->next) ++cnt;
        return cnt;
    }
    
    // O(1)
    void DoublyLinkedList::insertFront(int value) {
        Node* n=new Node(value,nullptr,head);
        if (head) head->prev=n;
        head=n;
        if (!tail) tail=n;
    }
    
    // O(n)
    void DoublyLinkedList::insertBack(int value) {
        Node* n=new Node(value,tail,nullptr);
        if (tail) tail->next=n;
        tail=n;
        if (!head) head=n;
    }
    
    // O(n)
    void DoublyLinkedList::insertAt(int value,size_t index) {
        if (index==0) {
            insertFront(value);
            return;
        }
        size_t i=0;
        Node* cur=head;
        while (cur&&i<index) {
            cur=cur->next;
            ++i;
        }
        if (!cur&&i==index) {

            insertBack(value);
        }
        else if (cur) {
            Node* n=new Node(value,cur->prev,cur);
            cur->prev->next=n;
            cur->prev=n;
        }
        else {
            throw std::out_of_range("insertAt: index out of range");
        }
    }
    
    // O(1)
    void DoublyLinkedList::deleteFront() {
        if (!head) return;
        Node* old=head;
        head=head->next;
        if (head) head->prev=nullptr;
        else tail=nullptr;
        delete old;
    }
    
    // O(n)
    void DoublyLinkedList::deleteBack() {
        if (!tail) return;
        Node* old=tail;
        tail=tail->prev;
        if (tail) tail->next=nullptr;
        else head=nullptr;
        delete old;
    }
    
    // O(n)
    void DoublyLinkedList::deleteAt(size_t index) {
        if (!head) return;
        if (index==0) {
            deleteFront();
            return;
        }
        size_t i=0;
        Node* cur=head;
        while (cur&&i<index) {
            cur=cur->next;
            ++i;
        }
        if (!cur) throw std::out_of_range("deleteAt: index out of range");
        if (cur==tail) {
            deleteBack();
        } else {
            cur->prev->next=cur->next;
            cur->next->prev=cur->prev;
            delete cur;
        }
    }
    
    // O(n)
    bool DoublyLinkedList::deleteValue(int value) {
        Node* cur=head;
        size_t idx=0;
        while (cur&&cur->data!=value) {
            cur=cur->next;
            ++idx;
        }
        if (!cur) return false;
        if (cur==head) deleteFront();
        else if (cur==tail) deleteBack();
        else {
            cur->prev->next=cur->next;
            cur->next->prev=cur->prev;
            delete cur;
        }
        return true;
    }
    
    // O(n)
    int DoublyLinkedList::search(int value) const {
        Node* cur=head;
        int idx=0;
        while (cur) {
            if (cur->data==value) return idx;
            cur=cur->next;
            ++idx;
        }
        return -1;
    }
    
    // O(n^2)
    void DoublyLinkedList::sort() {
        if (!head) return;
        for (Node* i=head;i;i=i->next) {
            for (Node* j=i->next;j;j=j->next) {
                if (i->data>j->data) {
                    std::swap(i->data,j->data);
                }
            }
        }
    }
    
    // O(1)
    void DoublyLinkedList::merge(DoublyLinkedList& other) {
        if (other.isEmpty()) return;
        if (isEmpty()) {
            head=other.head;
            tail=other.tail;
        } else {
            tail->next=other.head;
            other.head->prev=tail;
            tail=other.tail;
        }
        other.head=other.tail=nullptr;
    }
    
    void DoublyLinkedList::displayForward() const {
        for (Node* cur=head;cur;cur=cur->next) {
            std::cout<<cur->data<<" <-> ";
        }
        std::cout<<"NULL\n";
    }
    
    void DoublyLinkedList::displayBackward() const {
        for (Node* cur=tail;cur;cur=cur->prev) {
            std::cout<<cur->data<<" <-> ";
        }
        std::cout<<"NULL\n";
    }
    
    // O(n)
    void DoublyLinkedList::clear() {
        while (!isEmpty()) {
            deleteFront();
        }
    }
    
    void DoublyLinkedList::makeFromVector(const std::vector<int>& arr) {
        for (int v:arr) {
            insertBack(v);
        }
    }
    
    std::ostream& operator<<(std::ostream& out,const DoublyLinkedList& list) {
        for (Node* cur=list.head;cur;cur=cur->next) {
            out<<cur->data<<" <-> ";
        }
        out<<"NULL";
        return out;
    }
}
