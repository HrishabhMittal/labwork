#include <vector>
#include <deque>
#include <iostream>
std::vector<int> maxSlidingWindow(const std::vector<int>& nums, int k) {
    std::deque<int> dq;
    std::vector<int> result;
    for (int i=0;i<nums.size();++i) {
        while (!dq.empty()&&dq.front()<=i-k) dq.pop_front();
        while (!dq.empty()&&nums[dq.back()]<nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i>=k-1) result.push_back(nums[dq.front()]);
    }
    return result;
}
std::ostream& operator<<(std::ostream& out,const std::vector<int>& v) {
    std::cout<<"[ ";
    for (auto i:v) std::cout<<i<<" ";
    std::cout<<"]";
    return out;
}
int main() {
    std::cout<<maxSlidingWindow({1,3,-1,-3,5,3,6,7},3)<<std::endl;
    std::cout<<maxSlidingWindow({9,11,8,5,7,10},2)<<std::endl;
    std::cout<<maxSlidingWindow({1,-1},1)<<std::endl;
}
