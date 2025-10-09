#include <climits>
#include <iostream>
#include <ostream>
#include <vector>
int solve(std::vector<int>& vec) {
    if (vec.size()==0) return INT_MIN;
    if (vec.size()==1) return vec[0];
    int first=INT_MIN,second=INT_MIN;
    for (int i=0;i<vec.size();i++) {
        if (vec[i]>=first) {
            second=first;
            first=vec[i];
        } else if (vec[i]>=second) {
            second=vec[i];
        }
    }
    return second;
}
int main() {
    std::vector<int> arr={12, 35, 1, 10, 34, 1};
    std::cout<<solve(arr)<<std::endl;
}
