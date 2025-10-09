#pragma once

#include <iostream>
#include <vector>
namespace DoublyLinkedList {
    struct Node {
        int data;
        Node* prev;
        Node* next;
    
        Node(int value=0,Node* p=nullptr,Node* n=nullptr): data(value),prev(p),next(n) {}
    };
    class DoublyLinkedList {
    public:
        DoublyLinkedList(): head(nullptr),tail(nullptr) {}
        DoublyLinkedList(const std::vector<int>& arr): head(nullptr),tail(nullptr) {
            makeFromVector(arr);
        }
        ~DoublyLinkedList() {
            clear();
        }
    
        void insertFront(int value);
        void insertBack(int value);
        void insertAt(int value,size_t index);
    
        void deleteFront();
        void deleteBack();
        void deleteAt(size_t index);
        bool deleteValue(int value);
    
        int  search(int value) const;
        void sort();
        Node* max() const;
        void merge(DoublyLinkedList& other);
    

        bool isEmpty() const;
        size_t count() const;
        void displayForward() const;
        void displayBackward() const;

        friend std::ostream& operator<<(std::ostream& out,const DoublyLinkedList& list);
    
    private:
        Node* head;
        Node* tail;
    
        void clear();
        void makeFromVector(const std::vector<int>& arr);
    };
}
