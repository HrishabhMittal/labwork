//#define ONE_QUEUE
#include "stack.hpp"
#include <iostream>
#include <ostream>

int main() {
    Stack<int,5> st;
    std::cout<<"isEmpty: "<<st.isEmpty()<<std::endl;
    st.push(1);
    std::cout<<st.peek()<<std::endl;
    st.push(2);
    st.push(3);
    std::cout<<st.peek()<<std::endl;
    st.pop();
    st.push(4);
    std::cout<<st.peek()<<std::endl;
    std::cout<<"isEmpty: "<<st.isEmpty()<<std::endl;
}
