#include "circular_singly_linkedlist.hpp"
namespace CircularSingly {
    // O(n)
    bool CircularSinglyLinkedList::isCircular() const {
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
    // O(n)
    size_t CircularSinglyLinkedList::count() const {
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
    void CircularSinglyLinkedList::insertFront(int value) {
        Node* n = new Node(value);
        if (!head) {
            head = n;
            head->next = head;
        } else {
            Node* tail = head;
            while (tail->next != head) tail = tail->next;
            n->next = head;
            tail->next = n;
            head = n;
        }
    }
    // O(n)
    void CircularSinglyLinkedList::insertBack(int value) {
        Node* n = new Node(value);
        if (!head) {
            head = n;
            head->next = head;
        } else {
            Node* tail = head;
            while (tail->next != head) tail = tail->next;
            tail->next = n;
            n->next = head;
        }
    }
    // O(n)
    void CircularSinglyLinkedList::insertAt(int value, size_t index) {
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
        Node* n = new Node(value, cur->next);
        cur->next = n;
    }
    // O(1)
    void CircularSinglyLinkedList::deleteFront() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* tail = head;
        while (tail->next != head) tail = tail->next;
        Node* old = head;
        head = head->next;
        tail->next = head;
        delete old;
    }
    // O(n)
    void CircularSinglyLinkedList::deleteBack() {
        if (!head) return;
        if (head->next == head) {
            delete head;
            head = nullptr;
            return;
        }
        Node* prev = nullptr;
        Node* cur = head;
        while (cur->next != head) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = head;
        delete cur;
    }
    // O(n)
    void CircularSinglyLinkedList::deleteAt(size_t index) {
        if (!head) return;
        if (index == 0) {
            deleteFront();
            return;
        }
        size_t i = 1;
        Node* prev = head;
        Node* cur = head->next;
        while (cur != head && i < index) {
            prev = cur;
            cur = cur->next;
            ++i;
        }
        if (cur == head || i != index) {
            throw std::out_of_range("deleteAt: index out of range");
        }
        prev->next = cur->next;
        delete cur;
    }
    // O(n)
    bool CircularSinglyLinkedList::deleteValue(int value) {
        if (!head) return false;
        Node* prev = head;
        Node* cur = head->next;
        if (head->data == value) {
            deleteFront();
            return true;
        }
        while (cur != head && cur->data != value) {
            prev = cur;
            cur = cur->next;
        }
        if (cur == head) return false;
        prev->next = cur->next;
        delete cur;
        return true;
    }
    // O(n)
    int CircularSinglyLinkedList::search(int value) const {
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
    void CircularSinglyLinkedList::sort() {
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
    // O(n)
    void CircularSinglyLinkedList::merge(CircularSinglyLinkedList& other) {
        if (!other.head) return;
        if (!head) {
            head = other.head;
            other.head = nullptr;
            return;
        }
        Node* tail1 = head;
        while (tail1->next != head) tail1 = tail1->next;
        Node* tail2 = other.head;
        while (tail2->next != other.head) tail2 = tail2->next;
        tail1->next = other.head;
        tail2->next = head;
        other.head = nullptr;
    }
    void CircularSinglyLinkedList::display() const {
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
    // O(n)
    void CircularSinglyLinkedList::clear() {
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
    void CircularSinglyLinkedList::makeFromVector(const std::vector<int>& arr) {
        for (int v : arr) {
            insertBack(v);
        }
    }
    std::ostream& operator<<(std::ostream& out, const CircularSinglyLinkedList& list) {
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
