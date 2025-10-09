#include <iostream>
#include <string>
#include <stdexcept>
#include "linkedlist.hpp"
template<typename T>
class Stack {
    LinkedList::LinkedList<T> list;
public:
    Stack() = default;
    void pushBack(const T& e) {
        list.pushFront(e);
    }
    T popBack() {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow on popBack()");
        }
        auto node = list[0];
        T value = node->data;
        list.popFront();
        return value;
    }
    T peek() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack underflow on peek()");
        }
        return list[0]->data;
    }
    bool isEmpty() const {
        return list.size() == 0;
    }
    friend std::ostream& operator<<(std::ostream& out, const Stack<T>& stk) {
        out << stk.list;
        return out;
    }
};
bool isPalindrome(const std::string& s) {
    Stack<char> stk;
    for (char c : s) {
        stk.pushBack(c);
    }
    for (char c : s) {
        if (stk.popBack() != c) {
            return false;
        }
    }
    return true;
}
int main() {
    try {
        Stack<float> sf;
        sf.pushBack(3.14f);
        sf.pushBack(2.71f);
        sf.pushBack(1.41f);
        std::cout << "Float stack: " << sf << "[TOP]\n";
        std::cout << "Peek: " << sf.peek() << "\n";
        std::cout << "Pop:  " << sf.popBack()  << "\n";
        std::cout << "After popBack: " << sf << "[TOP]\n\n";
        Stack<std::string> ss;
        ss.pushBack("hello");
        ss.pushBack("world");
        std::cout << "String stack: " << ss << "[TOP]\n";
        std::cout << "Peek: " << ss.peek() << "\n";
        std::cout << "Pop:  " << ss.popBack()  << "\n";
        std::cout << "After popBack: " << ss << "[TOP]\n\n";
        std::string test1 = "racecar";
        std::string test2 = "stack";
        std::cout << "'" << test1 << "' is "
                  << (isPalindrome(test1) ? "" : "not ")
                  << "a palindrome.\n";
        std::cout << "'" << test2 << "' is "
                  << (isPalindrome(test2) ? "" : "not ")
                  << "a palindrome.\n";
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
    }
    return 0;
}
