#include "circular_doubly_linkedlist.hpp"
namespace CircularDoubly {
    // O(n)
    bool CircularDoublyLinkedList::isCircular() const {
        if (!head) return true;
        Node* slow = head;
        Node* fast = head->next;
        while (fast && fast->next) {
            if (slow == fast) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }
    // O(1)
    bool CircularDoublyLinkedList::isEmpty() const {
        return head == nullptr;
    }
    // O(n)
    size_t CircularDoublyLinkedList::count() const {
        if (!head) return 0;
        size_t cnt = 1;
        Node* cur = head->next;
        while (cur != head) {
            ++cnt;
            cur = cur->next;
        }
        return cnt;
    }
    // O(1)
    void CircularDoublyLinkedList::insertFront(int value) {
        Node* n = new Node(value);
        if (!head) {
            head = n;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            n->next = head;
            n->prev = tail;
            tail->next = n;
            head->prev = n;
            head = n;
        }
    }
    // O(1)
    void CircularDoublyLinkedList::insertBack(int value) {
        Node* n = new Node(value);
        if (!head) {
            head = n;
            head->next = head;
            head->prev = head;
        } else {
            Node* tail = head->prev;
            n->next = head;
            n->prev = tail;
            tail->next = n;
            head->prev = n;
        }
    }
    // O(n)
    void CircularDoublyLinkedList::insertAt(int value, size_t index) {
        if (index == 0) {
            insertFront(value);
            return;
        }
        size_t i = 1;
        Node* cur = head;
        while (cur->next != head && i < index) {
            cur = cur->next;
            ++i;
        }
        if (i != index) {
            if (cur->next == head && i == index) {
                insertBack(value);
                return;
            }
            throw std::out_of_range("insertAt: index out of range");
        }
        Node* n = new Node(value, cur->next, cur);
        cur->next->prev = n;
        cur->next = n;
    }
    // O(1)
    void CircularDoublyLinkedList::deleteFront() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* tail = head->prev;
        Node* old = head;
        head = head->next;
        head->prev = tail;
        tail->next = head;
        delete old;
    }
    // O(1)
    void CircularDoublyLinkedList::deleteBack() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* tail = head->prev;
        Node* newTail = tail->prev;
        newTail->next = head;
        head->prev = newTail;
        delete tail;
    }
    // O(n)
    void CircularDoublyLinkedList::deleteAt(size_t index) {
        if (!head) return;
        if (index == 0) {
            deleteFront();
            return;
        }
        size_t i = 1;
        Node* cur = head->next;
        while (cur != head && i < index) {
            cur = cur->next;
            ++i;
        }
        if (cur == head || i != index) {
            throw std::out_of_range("deleteAt: index out of range");
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
    }
    // O(n)
    bool CircularDoublyLinkedList::deleteValue(int value) {
        if (!head) return false;
        if (head->data == value) {
            deleteFront();
            return true;
        }
        Node* cur = head->next;
        while (cur != head && cur->data != value) {
            cur = cur->next;
        }
        if (cur == head) return false;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        return true;
    }
    // O(n)
    int CircularDoublyLinkedList::search(int value) const {
        if (!head) return -1;
        size_t idx = 0;
        Node* cur = head;
        do {
            if (cur->data == value) return idx;
            cur = cur->next;
            ++idx;
        } while (cur != head);
        return -1;
    }
    // O(n^2)
    void CircularDoublyLinkedList::sort() {
        if (!head || head->next == head) return;
        bool swapped;
        do {
            swapped = false;
            Node* cur = head;
            do {
                Node* nxt = cur->next;
                if (cur->data > nxt->data) {
                    std::swap(cur->data, nxt->data);
                    swapped = true;
                }
                cur = cur->next;
            } while (cur->next != head);
        } while (swapped);
    }
    // O(1)
    void CircularDoublyLinkedList::merge(CircularDoublyLinkedList& other) {
        if (!other.head) return;
        if (!head) {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node* tail1 = head->prev;
        Node* tail2 = other.head->prev;
        tail1->next = other.head;
        other.head->prev = tail1;
        tail2->next = head;
        head->prev = tail2;
        other.head = nullptr;
    }
    void CircularDoublyLinkedList::display() const {
        if (!head) {
            std::cout << "EMPTY\n";
            return;
        }
        Node* cur = head;
        do {
            std::cout << cur->data << " -> ";
            cur = cur->next;
        } while (cur != head);
        std::cout << "(back to head)\n";
    }
    void CircularDoublyLinkedList::displayReverse() const {
        if (!head) {
            std::cout << "EMPTY\n";
            return;
        }
        Node* cur = head->prev;
        do {
            std::cout << cur->data << " <- ";
            cur = cur->prev;
        } while (cur != head->prev);
        std::cout << "(back to tail)\n";
    }
    // O(n)
    void CircularDoublyLinkedList::clear() {
        if (!head) return;
        Node* cur = head->next;
        while (cur != head) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        delete head;
        head = nullptr;
    }
    void CircularDoublyLinkedList::makeFromVector(const std::vector<int>& arr) {
        for (int v : arr) {
            insertBack(v);
        }
    }
    std::ostream& operator<<(std::ostream& out, const CircularDoublyLinkedList& list) {
        if (!list.head) {
            out << "EMPTY";
            return out;
        }
        Node* cur = list.head;
        do {
            out << cur->data << " -> ";
            cur = cur->next;
        } while (cur != list.head);
        out << "(head)";
        return out;
    }
}
