#include <iostream>
#include <ostream>
#include <stack>
#include <vector>
std::vector<int> nextGreater(const std::vector<int>& vec) {
    if (vec.size()==0) return vec;
    std::stack<int> st;
    st.push(0);
    std::vector<int> out(vec.size(),-1);
    for (int i=1;i<vec.size();i++) {
        while (!st.empty()&&vec[i]>vec[st.top()]) {
            out[st.top()]=vec[i];
            st.pop();
        }
        st.push(i);
    }
    return out;
}
std::ostream& operator<<(std::ostream& out,const std::vector<int>& v) {
    std::cout<<"[ ";
    for (auto i:v) std::cout<<i<<" ";
    std::cout<<"]";
    return out;
}
int main() {
    std::cout<<nextGreater({4,5,2,10})<<std::endl;
    std::cout<<nextGreater({3,7,1,7,8})<<std::endl;
    std::cout<<nextGreater({1,2,3,4})<<std::endl;
}
