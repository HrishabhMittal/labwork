
#include <iostream>
#include <vector>
#include "linkedlist.hpp"

int main() {
    LinkedList::LinkedList list({2,7,3,5,4,1,7,6});
    std::cout<<"Original list: "<<list<<std::endl;
    while (true) {
        std::string cmd;
        std::cout<<"commands: insert_at,remove_at,remove,sort,push_back,pop_back,push_front,pop_front,reverse,size,search,merge ";
        std::cout<<"enter command: ";
        std::cin>>cmd;
        if (cmd=="insert_at") {
            int value;
            size_t index;
            std::cout<<"Value to insert: ";
            std::cin>>value;
            std::cout<<"Index: ";
            std::cin>>index;
            list.insertAt(value,index);
        } else if (cmd=="remove_at") {
            size_t index;
            std::cout<<"Index to remove: ";
            std::cin>>index;
            list.removeAt(index);
        } else if (cmd=="remove") {
            int value;
            std::cout<<"Value to remove: ";
            std::cin>>value;
            if (!list.removeValue(value)) {
                std::cout<<"Value not found"<<std::endl;
            }
        } else if (cmd=="sort") {
            list.sort();
        } else if (cmd=="push_back") {
            int value;
            std::cout<<"Value to push_back: ";
            std::cin>>value;
            list.pushBack(value);
        } else if (cmd=="pop_back") {
            list.popBack();
        } else if (cmd=="push_front") {
            int value;
            std::cout<<"Value to push_front: ";
            std::cin>>value;
            list.pushFront(value);
        } else if (cmd=="pop_front") {
            list.popFront();
        } else if (cmd=="reverse") {
            list.reverse();
        } else if (cmd=="size") {
            std::cout<<"Size: "<<list.size()<<std::endl;
        } else if (cmd=="search") {
            int value;
            std::cout<<"Value to search: ";
            std::cin>>value;
            LinkedList::Node* node=list.search(value);
            if (node) {
                std::cout<<"Found node with value "<<node->data<<std::endl;
            } else {
                std::cout<<"Value not found"<<std::endl;
            }
        } else if (cmd=="merge") {
            int n;
            std::cout<<"Number of elements in second list: ";
            std::cin>>n;
            std::vector<int> vals(n);
            std::cout<<"Enter elements: ";
            for (int i=0;i<n;i++) {
                std::cin>>vals[i];
            }
            LinkedList::LinkedList other(vals);
            list.merge(other);
        } else if (cmd=="exit") break;
        else if (cmd=="max") {
            std::cout<<list.max()->data<<std::endl;
        }
        else {
            std::cout<<"Unknown command"<<std::endl;
        } 

        std::cout<<"Resulting list: "<<list<<std::endl;
    }
    return 0;
}
