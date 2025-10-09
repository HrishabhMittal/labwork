#include <climits>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>
int getRandomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
std::vector<int> random_arr(int n) {
    std::vector<int> v;
    for (int i=0;i<n;i++) v.push_back(getRandomInt(0,200));
    return v;
}
std::ostream& operator<<(std::ostream& out,const std::vector<int>& arr) {
    out<<"[ ";
    for (auto i:arr) out<<i<<" ";
    return out<<"]";
}
bool check_sorted(const std::vector<int>& v) {
    for (int i=1;i<v.size();i++) {
        if (v[i]<v[i-1]) return 0;
    }
    return 1;
}

