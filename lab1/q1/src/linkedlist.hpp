#pragma once

#include <iostream>
#include <vector>

namespace LinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int data=0, Node* next=nullptr): data(data), next(next) {}
    };
    class LinkedList {
    public:
        LinkedList(): head(nullptr) {}
        LinkedList(const std::vector<int>& arr): head(nullptr) {
            makeFromVector(arr);
        }
        ~LinkedList() {
            clear();
        }
    
        void pushFront(int value);
        void pushBack(int value);
        void popFront();
        void popBack();
    
        Node* max() const;
        void insertAt(int value, size_t index);
        void removeAt(size_t index);
    
        Node* search(int value) const;
        bool removeValue(int value);
    
        size_t size() const;
        void sort();
    
        void merge(LinkedList& other);
        void reverse();
    
        Node* operator[](size_t index) const;
        friend std::ostream& operator<<(std::ostream& out, const LinkedList& list); 
    private:
        Node* head;
    
        void clear();
        void makeFromVector(const std::vector<int>& arr);
    };
    
}
