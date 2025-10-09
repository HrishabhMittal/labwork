#pragma once

#include <iostream>
#include <vector>
namespace LinkedList {
    template<typename T>
    struct Node {
        T data;
        Node<T>* next;
        Node(T data=0, Node* next=nullptr): data(data), next(next) {}
    };
    template<typename T>
    class LinkedList {
    public:
        Node<T>* head;
        LinkedList(): head(nullptr) {}
        LinkedList(const std::vector<T>& arr): head(nullptr) {
            makeFromVector(arr);
        }
        ~LinkedList() {
            clear();
        }
        // friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list); 
        void pushFront(T value) {
            head = new Node<T>(value, head);
        }
        // O(n)
        void pushBack(T value) {
            if (!head) {
                head = new Node<T>(value);
                return;
            }
            Node<T>* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = new Node<T>(value);
        }
        
        // O(1)
        void popFront() {
            if (!head) return;
            Node<T>* old = head;
            head = head->next;
            old->next = nullptr;
            delete old;
        }
        
        // O(n)
        void popBack() {
            if (!head) return;
            if (!head->next) {
                delete head;
                head = nullptr;
                return;
            }
            Node<T>* cur = head;
            while (cur->next->next) cur = cur->next;
            delete cur->next;
            cur->next = nullptr;
        }
        
        // O(n)
        void insertAt(T value, size_t index) {
            if (index == 0) {
                pushFront(value);
                return;
            }
            Node<T>* cur = head;
            size_t i = 1;
            while (cur && i < index) {
                cur = cur->next;
                ++i;
            }
            if (!cur) throw std::out_of_range("index out of range");
            cur->next = new Node<T>(value, cur->next);
        }
        
        // O(n)
        void removeAt(size_t index) {
            if (!head) return;
            if (index == 0) {
                popFront();
                return;
            }
            Node<T>* cur = head;
            size_t i = 1;
            while (cur->next && i < index) {
                cur = cur->next;
                ++i;
            }
            if (!cur->next) throw std::out_of_range("index out of range");
            Node<T>* del = cur->next;
            cur->next = del->next;
            del->next = nullptr;
            delete del;
        }
        Node<T>* max() const {
            Node<T>* cur=head;
            Node<T>* out=nullptr;
            for (;cur;cur=cur->next) {
                if (out==nullptr) out=cur;
                else {
                    if (out->data<cur->data) out=cur;
                }
            } 
            return out;
        }
        // O(n)
        Node<T>* search(T value) const {
            Node<T>* cur = head;
            while (cur && cur->data != value) {
                cur = cur->next;
            }
            return cur;
        }
        
        // O(n)
        bool removeValue(T value) {
            if (!head) return false;
            if (head->data == value) {
                popFront();
                return true;
            }
            Node<T>* cur = head;
            while (cur->next && cur->next->data != value) {
                cur = cur->next;
            }
            if (!cur->next) return false;
            Node<T>* del = cur->next;
            cur->next = del->next;
            del->next = nullptr;
            delete del;
            return true;
        }
        
        // O(n)
        size_t size() const {
            size_t count = 0;
            for (Node<T>* cur = head; cur; cur = cur->next) {
                ++count;
            }
            return count;
        }
        
        // O(n^2)
        void sort() {
            for (Node<T>* i = head; i; i = i->next) {
                for (Node<T>* j = i->next; j; j = j->next) {
                    if (i->data > j->data) {
                        std::swap(i->data, j->data);
                    }
                }
            }
        }
        
        // O(1)
        void merge(LinkedList<T>& other) {
            if (!head) {
                head = other.head;
            } else {
                Node<T>* cur = head;
                while (cur->next) cur = cur->next;
                cur->next = other.head;
            }
            other.head = nullptr;
        }
        
        // O(n)
        void reverse() {
            Node<T>* prev = nullptr;
            Node<T>* cur  = head;
            while (cur) {
                Node<T>* next = cur->next;
                cur->next = prev;
                prev = cur;
                cur = next;
            }
            head = prev;
        }
        
        // O(n)
        Node<T>* operator[](size_t index) const {
            Node<T>* cur = head;
            while (cur && index--) {
                cur = cur->next;
            }
            return cur;
        }
        
    private:
    
        void makeFromVector(const std::vector<T>& arr) {
            for (T val : arr) {
                pushBack(val);
            }
        }
        // O(n)
        void clear() {
            while (head) {
                popFront();
            }
        }
    };
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list) {
        Node<T>* cur = list.head;
        while (cur) {
            out << cur->data << "->";
            cur = cur->next;
        }
        // out << "[END]";
        return out;
    }
}
