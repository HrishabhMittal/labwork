#include <ostream>
#include <vector>
#include <stack>
#include <iostream>
std::vector<int> warmerDay(const std::vector<int>& vec) {
    if (vec.size()==0) return vec;
    std::stack<int> st;
    st.push(0);
    std::vector<int> out(vec.size(),0);
    for (int i=1;i<vec.size();i++) {
        while (!st.empty()&&vec[i]>vec[st.top()]) {
            out[st.top()]=i-st.top();
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
    std::cout<<warmerDay({73,74,75,71,69,72,76,73})<<std::endl;
    std::cout<<warmerDay({30,40,50,60})<<std::endl;
    std::cout<<warmerDay({30,60,90})<<std::endl;
}
