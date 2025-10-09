#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>

namespace CircularDoubly {

    struct Node {
        int data;
        Node* next;
        Node* prev;
        Node(int value = 0, Node* nxt = nullptr, Node* prv = nullptr) : data(value), next(nxt), prev(prv) {}
    };
    
    class CircularDoublyLinkedList {
    public:
        CircularDoublyLinkedList() : head(nullptr) {}
        
        CircularDoublyLinkedList(const std::vector<int>& arr) : head(nullptr) {
            makeFromVector(arr);
        }
        
        ~CircularDoublyLinkedList() {
            clear();
        }
        
        void insertFront(int value);
        void insertBack(int value);
        void insertAt(int value, size_t index);
        void deleteFront();
        void deleteBack();
        void deleteAt(size_t index);
        bool deleteValue(int value);
        int search(int value) const;
        void sort();
        void merge(CircularDoublyLinkedList& other);
        void display() const;
        void displayReverse() const;
        size_t count() const;
        bool isCircular() const;
        bool isEmpty() const;
        
        friend std::ostream& operator<<(std::ostream& out, const CircularDoublyLinkedList& list);
    
    private:
        Node* head;
        void clear();
        void makeFromVector(const std::vector<int>& arr);
    };
    
    std::ostream& operator<<(std::ostream& out, const CircularDoublyLinkedList& list);

}
