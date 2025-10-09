#include <iostream>
#include <ostream>
#include <stack>
#include <string>
bool parenOrder(const std::string& str) {
    std::stack<char> st;
    for (auto i:str) {
        switch (i) {
            case '(':
            case '{':
            case '[':
                st.push(i);
                break;
            case ')':
                if (st.empty()||st.top()!='(') return false;
                st.pop();
                break;
            case '}':
                if (st.empty()||st.top()!='{') return false;
                st.pop();
                break;
            case ']':
                if (st.empty()||st.top()!='[') return false;
                st.pop();
                break;
            default:
                return false;
        }
    }
    return st.empty();
}
void printBool(bool b) {
    std::cout<<(b?"True":"False")<<std::endl;
}
int main() {
    printBool(parenOrder("()[]{}"));
    printBool(parenOrder("(]"));
    printBool(parenOrder("{[()]}"));
    printBool(parenOrder("([)]"));
}
