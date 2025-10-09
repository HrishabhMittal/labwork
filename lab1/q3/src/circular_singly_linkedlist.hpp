#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
namespace CircularSingly {
    struct Node {
        int data;
        Node* next;
        Node(int value=0,Node* nxt=nullptr): data(value), next(nxt) {}
    };
    class CircularSinglyLinkedList {
    public:
        CircularSinglyLinkedList() : head(nullptr) {}
        CircularSinglyLinkedList(const std::vector<int>& arr) : head(nullptr) {
            makeFromVector(arr);
        }
        ~CircularSinglyLinkedList() {
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
        void merge(CircularSinglyLinkedList& other);
        void display() const;               
        size_t count() const;
        bool isCircular() const;
        friend std::ostream& operator<<(std::ostream& out, const CircularSinglyLinkedList& list);
    private:
        Node* head;
        void clear();
        void makeFromVector(const std::vector<int>& arr);
    };
} 
