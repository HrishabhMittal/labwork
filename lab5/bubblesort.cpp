#include "utils.cpp"
#include <utility>
#define BENCHMARK
#define YN(x) (x?"YES":"NO")
#ifdef BENCHMARK 
#define benchmark(x) x
#else
#define benchmark(x)
#endif
void bubble_sort(std::vector<int>& arr) {
    benchmark(int iterations=0);
    for (int i=0;i<arr.size();i++) {
        for (int j=0;j<arr.size();j++) {
            benchmark(iterations++);
            if (arr[j]>arr[i]) std::swap(arr[j],arr[i]);
        }
    }
    benchmark(std::cout<<"bubble_sort ended with "<<iterations<<" iterations."<<std::endl);
}
void bubble_sort_with_early_stop(std::vector<int>& arr) {
    benchmark(int iterations=0);
    for (int i=0;i<arr.size();i++) {
        bool b=1;
        for (int j=0;j<arr.size();j++) {
            if (j<i&&arr[j]>arr[i]) b=0;
            if (i<j&&arr[i]>arr[j]) b=0;
            if (arr[j]>arr[i]) std::swap(arr[j],arr[i]);
            benchmark(iterations++);
        }
        if (b) break;
    }
    benchmark(std::cout<<"bubble_sort_with_early_stop ended with "<<iterations<<" iterations."<<std::endl);
}
int main() {
    auto r=random_arr(20);
    auto r_copy=r;
    std::cout<<r<<std::endl;
    bubble_sort(r);
    std::cout<<YN(check_sorted(r))<<std::endl;
    bubble_sort_with_early_stop(r_copy);
    std::cout<<YN(check_sorted(r_copy))<<std::endl;
}
