#include <bits/stdc++.h>

struct Stats {
    long long comps = 0;
    long long swaps = 0;
    double time_ms = 0;
    void reset() { comps = swaps = 0; time_ms = 0; }
};

template<typename Func>
Stats run_sort(Func sort_func, const std::vector<int>& arr) {
    Stats st;
    std::vector<int> a = arr;
    auto t0 = std::chrono::high_resolution_clock::now();
    sort_func(a, st);
    auto t1 = std::chrono::high_resolution_clock::now();
    st.time_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return st;
}

// 1. Bubble Sort
void bubble_basic(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int i = 0; i < n; i++) {
        for(int j = 0; j + 1 < n - i; j++) {
            st.comps++;
            if(a[j] > a[j+1]) {
                std::swap(a[j], a[j+1]);
                st.swaps++;
            }
        }
    }
}
void bubble_early(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int i = 0; i < n; i++) {
        bool swapped = false;
        for(int j = 0; j + 1 < n - i; j++) {
            st.comps++;
            if(a[j] > a[j+1]) {
                std::swap(a[j], a[j+1]);
                st.swaps++;
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}

// 2. Selection Sort
void selection_sort(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int i = 0; i + 1 < n; i++) {
        int mn = i;
        for(int j = i + 1; j < n; j++) {
            st.comps++;
            if(a[j] < a[mn]) mn = j;
        }
        if(mn != i) {
            std::swap(a[i], a[mn]);
            st.swaps++;
        }
    }
}

// 3. Insertion Sort
void insertion_sort(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int i = 1; i < n; i++) {
        int key = a[i], j = i - 1;
        while(j >= 0) {
            st.comps++;
            if(a[j] > key) {
                a[j+1] = a[j];
                st.swaps++;
                j--;
            } else break;
        }
        a[j+1] = key;
    }
}

// 4. Quick Sort Variants
int partition_first(std::vector<int>& a, int l, int r, Stats& st) {
    int pivot = a[l], i = l + 1;
    for(int j = l + 1; j <= r; j++) {
        st.comps++;
        if(a[j] < pivot) {
            std::swap(a[j], a[i++]);
            st.swaps++;
        }
    }
    std::swap(a[l], a[i-1]);
    st.swaps++;
    return i - 1;
}
int partition_last(std::vector<int>& a, int l, int r, Stats& st) {
    std::swap(a[l], a[r]);
    st.swaps++;
    return partition_first(a, l, r, st);
}
int partition_rand(std::vector<int>& a, int l, int r, Stats& st) {
    int idx = l + std::rand() % (r - l + 1);
    std::swap(a[l], a[idx]);
    st.swaps++;
    return partition_first(a, l, r, st);
}
void quick_rec(std::vector<int>& a, int l, int r, Stats& st, int mode) {
    if(l >= r) return;
    int p = (mode == 1 ? partition_last(a,l,r,st)
             : mode == 2 ? partition_rand(a,l,r,st)
             : partition_first(a,l,r,st));
    quick_rec(a, l, p-1, st, mode);
    quick_rec(a, p+1, r, st, mode);
}
void quick_sort_first(std::vector<int>& a, Stats& st) { quick_rec(a, 0, static_cast<int>(a.size())-1, st, 0); }
void quick_sort_last (std::vector<int>& a, Stats& st) { quick_rec(a, 0, static_cast<int>(a.size())-1, st, 1); }
void quick_sort_rand (std::vector<int>& a, Stats& st) { quick_rec(a, 0, static_cast<int>(a.size())-1, st, 2); }

// 5. Merge Sort
void merge_merge(std::vector<int>& a, int l, int m, int r, Stats& st) {
    int n1 = m - l + 1, n2 = r - m;
    std::vector<int> L(a.begin()+l, a.begin()+m+1),
                     R(a.begin()+m+1, a.begin()+r+1);
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2) {
        st.comps++;
        if(L[i] <= R[j]) a[k++] = L[i++];
        else { a[k++] = R[j++]; st.swaps++; }
    }
    while(i < n1) a[k++] = L[i++];
    while(j < n2) a[k++] = R[j++];
}
void merge_rec(std::vector<int>& a, int l, int r, Stats& st) {
    if(l < r) {
        int m = l + (r - l) / 2;
        merge_rec(a, l, m, st);
        merge_rec(a, m+1, r, st);
        merge_merge(a, l, m, r, st);
    }
}
void merge_sort_rec(std::vector<int>& a, Stats& st) { merge_rec(a, 0, static_cast<int>(a.size())-1, st); }
void merge_sort_it(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int sz = 1; sz < n; sz <<= 1) {
        for(int l = 0; l < n; l += 2*sz) {
            int m = std::min(l+sz-1, n-1);
            int r = std::min(l+2*sz-1, n-1);
            if(m < r) merge_merge(a, l, m, r, st);
        }
    }
}

// 6. Heap Sort
void heapify(std::vector<int>& a, int n, int i, Stats& st) {
    int largest = i, l = 2*i+1, r = 2*i+2;
    if(l < n) { st.comps++; if(a[l] > a[largest]) largest = l; }
    if(r < n) { st.comps++; if(a[r] > a[largest]) largest = r; }
    if(largest != i) {
        std::swap(a[i], a[largest]);
        st.swaps++;
        heapify(a, n, largest, st);
    }
}
void heap_sort(std::vector<int>& a, Stats& st) {
    int n = static_cast<int>(a.size());
    for(int i = n/2 - 1; i >= 0; i--) heapify(a, n, i, st);
    for(int i = n-1; i > 0; i--) {
        std::swap(a[0], a[i]);
        st.swaps++;
        heapify(a, i, 0, st);
    }
}

// Test harness with skip for large n
void test_case(const std::string& name, const std::vector<int>& base) {
    std::cout << "=== " << name << " (n=" << base.size() << ") ===\n";
    bool small = base.size() <= 10000;

    auto run2 = [&](auto&& sort_fn, const std::string& label){
        Stats st = run_sort(sort_fn, base);
        std::cout << std::setw(20) << label
                  << "  comps=" << st.comps
                  << " swaps=" << st.swaps
                  << " time=" << st.time_ms << "ms\n";
    };

    if(small) {
        run2(bubble_basic,    "BubbleBasic");
        run2(bubble_early,    "BubbleEarly");
        run2(selection_sort,  "SelectionSort");
        run2(insertion_sort,  "InsertionSort");
    } else {
        std::cout << "  [Skipping O(n^2) sorts for large n]\n";
    }

    run2(quick_sort_first, "QuickFirst");
    run2(quick_sort_last,  "QuickLast");
    run2(quick_sort_rand,  "QuickRandom");
    run2(merge_sort_rec,   "MergeRecursive");
    run2(merge_sort_it,    "MergeIterative");
    run2(heap_sort,        "HeapSort");

    std::cout << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<std::vector<int>> tests = {
        {},                          // empty
        {42},                        // single-element
        {1,2,3,4,5,6,7,8,9,10},      // sorted
        {10,9,8,7,6,5,4,3,2,1},      // reverse-sorted
        std::vector<int>(10, 5)      // identical
    };

    std::vector<int> large(100000);
    std::iota(large.begin(), large.end(), 0);
    std::shuffle(large.begin(), large.end(), std::mt19937(std::random_device()()));
    tests.push_back(large);

    const char* names[] = {
        "Empty", "Single", "Sorted", "Reverse", "Identical", "LargeRandom"
    };

    for(int i = 0; i < static_cast<int>(tests.size()); i++) {
        test_case(names[i], tests[i]);
    }

    return 0;
}
