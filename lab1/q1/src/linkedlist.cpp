#include "linkedlist.hpp"

namespace LinkedList {
    // O(1)
    void LinkedList::pushFront(int value) {
        head = new Node(value, head);
    }
    // O(n)
    void LinkedList::pushBack(int value) {
        if (!head) {
            head = new Node(value);
            return;
        }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = new Node(value);
    }
    
    // O(1)
    void LinkedList::popFront() {
        if (!head) return;
        Node* old = head;
        head = head->next;
        old->next = nullptr;
        delete old;
    }
    
    // O(n)
    void LinkedList::popBack() {
        if (!head) return;
        if (!head->next) {
            delete head;
            head = nullptr;
            return;
        }
        Node* cur = head;
        while (cur->next->next) cur = cur->next;
        delete cur->next;
        cur->next = nullptr;
    }
    
    // O(n)
    void LinkedList::insertAt(int value, size_t index) {
        if (index == 0) {
            pushFront(value);
            return;
        }
        Node* cur = head;
        size_t i = 1;
        while (cur && i < index) {
            cur = cur->next;
            ++i;
        }
        if (!cur) throw std::out_of_range("index out of range");
        cur->next = new Node(value, cur->next);
    }
    
    // O(n)
    void LinkedList::removeAt(size_t index) {
        if (!head) return;
        if (index == 0) {
            popFront();
            return;
        }
        Node* cur = head;
        size_t i = 1;
        while (cur->next && i < index) {
            cur = cur->next;
            ++i;
        }
        if (!cur->next) throw std::out_of_range("index out of range");
        Node* del = cur->next;
        cur->next = del->next;
        del->next = nullptr;
        delete del;
    }
    Node* LinkedList::max() const {
        Node* cur=head;
        Node* out=nullptr;
        for (;cur;cur=cur->next) {
            if (out==nullptr) out=cur;
            else {
                if (out->data<cur->data) out=cur;
            }
        } 
        return out;
    }
    // O(n)
    Node* LinkedList::search(int value) const {
        Node* cur = head;
        while (cur && cur->data != value) {
            cur = cur->next;
        }
        return cur;
    }
    
    // O(n)
    bool LinkedList::removeValue(int value) {
        if (!head) return false;
        if (head->data == value) {
            popFront();
            return true;
        }
        Node* cur = head;
        while (cur->next && cur->next->data != value) {
            cur = cur->next;
        }
        if (!cur->next) return false;
        Node* del = cur->next;
        cur->next = del->next;
        del->next = nullptr;
        delete del;
        return true;
    }
    
    // O(n)
    size_t LinkedList::size() const {
        size_t count = 0;
        for (Node* cur = head; cur; cur = cur->next) {
            ++count;
        }
        return count;
    }
    
    // O(n^2)
    void LinkedList::sort() {
        for (Node* i = head; i; i = i->next) {
            for (Node* j = i->next; j; j = j->next) {
                if (i->data > j->data) {
                    std::swap(i->data, j->data);
                }
            }
        }
    }
    
    // O(1)
    void LinkedList::merge(LinkedList& other) {
        if (!head) {
            head = other.head;
        } else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = other.head;
        }
        other.head = nullptr;
    }
    
    // O(n)
    void LinkedList::reverse() {
        Node* prev = nullptr;
        Node* cur  = head;
        while (cur) {
            Node* next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;
    }
    
    // O(n)
    Node* LinkedList::operator[](size_t index) const {
        Node* cur = head;
        while (cur && index--) {
            cur = cur->next;
        }
        return cur;
    }
    
    std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
        Node* cur = list.head;
        while (cur) {
            out << cur->data << "->";
            cur = cur->next;
        }
        out << "[END]";
        return out;
    }
    
    // O(n)
    void LinkedList::clear() {
        while (head) {
            popFront();
        }
    }
    
    void LinkedList::makeFromVector(const std::vector<int>& arr) {
        for (int val : arr) {
            pushBack(val);
        }
    }
}
