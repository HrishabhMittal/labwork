#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
void rotate(std::vector<int>& vec,int k) {
    int s=vec.size();
    if (s==0) return;
    k%=s;
    if (s%k) {
        int temp=vec[0];
        for (int i=0,j=0;i<s;i++,j+=k) {
            std::swap(temp,vec[(j+k)%s]);
        }
    } else for (int i=0;i<s;i++) {
        std::swap(vec[i%k],vec[(i+k)%s]);
    }
}
std::ostream& operator<<(std::ostream& out,const std::vector<int>& v) {
    std::cout<<"[ ";
    for (auto i:v) std::cout<<i<<" ";
    std::cout<<"]";
    return out;
}
int main() {
    std::vector<int> vec{1,2,3,4,5,6,7};
    rotate(vec,3);
    std::cout<<vec<<std::endl;
    
    std::vector<int> vec1{-1,-100,3,99};
    rotate(vec1,2);
    std::cout<<vec1<<std::endl;
    
    std::vector<int> vec2{1,2,3};
    rotate(vec2,4);
    std::cout<<vec2<<std::endl;
}
