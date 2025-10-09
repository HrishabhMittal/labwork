
// main.cpp
#include <iostream>
#include <ostream>
#include <vector>
#include "circular_singly_linkedlist.hpp"

int main() {
    using namespace CircularSingly;

    CircularSinglyLinkedList list({2, 7, 3, 5, 4, 1, 7, 6});
    std::cout << "Initial circular list: " << list << std::endl;

    std::cout << "Commands:\n insert_front  insert_back  insert_at delete_front  delete_back  delete_at  delete_value search  sort  merge display  count  is_circular exit"<<std::endl;

    std::string cmd;
    while (true) {
        std::cout << "\nEnter command: ";
        std::cin >> cmd;

        if (cmd == "insert_front") {
            int v; std::cin >> v;
            list.insertFront(v);
        }
        else if (cmd == "insert_back") {
            int v; std::cin >> v;
            list.insertBack(v);
        }
        else if (cmd == "insert_at") {
            int v; size_t idx; std::cin >> v >> idx;
            list.insertAt(v, idx);
        }
        else if (cmd == "delete_front") {
            list.deleteFront();
        }
        else if (cmd == "delete_back") {
            list.deleteBack();
        }
        else if (cmd == "delete_at") {
            size_t idx; std::cin >> idx;
            list.deleteAt(idx);
        }
        else if (cmd == "delete_value") {
            int v; std::cin >> v;
            if (!list.deleteValue(v))
                std::cout << "Value not found"<<std::endl;
        }
        else if (cmd == "search") {
            int v; std::cin >> v;
            int idx = list.search(v);
            std::cout << (idx >= 0 ? "Found at index " + std::to_string(idx):"Not found")<< ""<<std::endl;
        }
        else if (cmd == "sort") {
            list.sort();
        }
        else if (cmd == "merge") {
            size_t n; std::cin >> n;
            std::vector<int> vals(n);
            for (size_t i = 0; i < n; ++i) std::cin >> vals[i];
            CircularSinglyLinkedList other(vals);
            list.merge(other);
        }
        else if (cmd == "display") {
            list.display();
        }
        else if (cmd == "count") {
            std::cout << "Count: " << list.count() << ""<<std::endl;
        }
        else if (cmd == "is_circular") {
            std::cout << (list.isCircular() ? "Circular" : "Not circular")<<std::endl;
        }
        else if (cmd == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command"<<std::endl;
        }

        std::cout << "List now: " << list << ""<<std::endl;
    }

    return 0;
}
