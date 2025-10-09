// main.cpp

#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include "circular_doubly_linkedlist.hpp"

int main() {
    using namespace CircularDoubly;
    
    CircularDoublyLinkedList list({2, 7, 3, 5, 4, 1, 7, 6});
    std::cout << "Initial circular doubly linked list: " << list << std::endl;
    
    std::cout << "Commands:\n insert_front insert_back insert_at delete_front delete_back delete_at delete_value search sort merge display display_reverse count is_circular is_empty exit"<<std::endl;
    
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "insert_front") {
            int v; 
            std::cin >> v;
            list.insertFront(v);
        }
        else if (cmd == "insert_back") {
            int v; 
            std::cin >> v;
            list.insertBack(v);
        }
        else if (cmd == "insert_at") {
            int v; 
            size_t idx; 
            std::cin >> v >> idx;
            try {
                list.insertAt(v, idx);
            } catch (const std::out_of_range& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (cmd == "delete_front") {
            list.deleteFront();
        }
        else if (cmd == "delete_back") {
            list.deleteBack();
        }
        else if (cmd == "delete_at") {
            size_t idx; 
            std::cin >> idx;
            try {
                list.deleteAt(idx);
            } catch (const std::out_of_range& e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        else if (cmd == "delete_value") {
            int v; 
            std::cin >> v;
            if (!list.deleteValue(v))
                std::cout << "Value not found\n";
        }
        else if (cmd == "search") {
            int v; 
            std::cin >> v;
            int idx = list.search(v);
            std::cout << (idx >= 0 ? "Found at index " + std::to_string(idx)
                                   : "Not found")
                      << std::endl;
        }
        else if (cmd == "sort") {
            list.sort();
        }
        else if (cmd == "merge") {
            size_t n; 
            std::cin >> n;
            std::vector<int> vals(n);
            for (size_t i = 0; i < n; ++i) std::cin >> vals[i];
            CircularDoublyLinkedList other(vals);
            list.merge(other);
        }
        else if (cmd == "display") {
            list.display();
        }
        else if (cmd == "display_reverse") {
            list.displayReverse();
        }
        else if (cmd == "count") {
            std::cout << "Count: " << list.count() << std::endl;
        }
        else if (cmd == "is_circular") {
            std::cout << (list.isCircular() ? "Circular\n" : "Not circular\n");
        }
        else if (cmd == "is_empty") {
            std::cout << (list.isEmpty() ? "Empty\n" : "Not empty\n");
        }
        else if (cmd == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command\n";
        }
        
        std::cout << "List now: " << list << std::endl;
    }
    
    return 0;
}
