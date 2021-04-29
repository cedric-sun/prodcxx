#include <bits/stdc++.h>

using namespace std;

// 0-based max binary heap

inline int parent(int i) { return (i - 1) / 2; } // mind that parent(0) is 0

inline int left(int i) { return i * 2 + 1; }

inline int right(int i) { return i * 2 + 2; }

// make a[0,i] a heap, provided that a[0,i-1] is already a heap
void sift_up(vector<int> &a, int i) {
    int p = parent(i);
    while (p >= 0 && a[i] > a[p]) { // a[0] > a[0] is false, so we safe
        swap(a[i], a[p]);
        i = p;
        p = parent(p);
    }
}

// Within the heap represented by a[0,end),
// make a[i] and its subtree a heap, provided that left and right are already heap
void sift_down(vector<int> &a, int i, const int end) {
    while (true) {
        int max_i = i;
        const int l = left(i), r = right(i);
        if (l < end && a[l] > a[max_i]) // we being lazy when a[l] == a[r] == a[i]
            max_i = l;
        if (r < end && a[r] > a[max_i])
            max_i = r;
        if (max_i != i) {
            swap(a[max_i], a[i]);
            i = max_i;
        } else {
            break;
        }
    }
}

// O(n). Proof: https://en.wikipedia.org/wiki/Binary_heap#Building_a_heap
void heapify_bottom_up(vector<int> &a) {
    for (int i = parent(a.size() - 1); i >= 0; --i)
        sift_down(a, i, a.size());
}

// O(nlogn). This mimics keeping pushing into an empty heap
void heapify_top_down(vector<int> &a) {
    for (int i = 1; i < a.size(); ++i)
        sift_up(a, i);
}

// always O(nlogn) regardless which heapify is used
void heap_sort(vector<int> &a) {
    heapify_bottom_up(a); // or heapify_top_down(a);
    for (int end = a.size() - 1; end > 0; --end) { // mind end > 0: we stop when heap has the last element
        swap(a[0], a[end]);
        sift_down(a, 0, end);
    }
}

class myheap {
private:
    vector<int> a;
public:
    void push(int value) {
        a.push_back(value);
        sift_up(a, a.size() - 1);
    }

    const int &top() const {
        return a.front();
    }

    void pop() {
        swap(a.front(), a.back());
        a.pop_back();
        sift_down(a, 0, a.size());
    }
};

void test_heap_sort() {
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{};
    constexpr int MAXN = 100000;
    vector<int> data(MAXN), ref(MAXN);
    for (int t = 0; t < 15; t++) {
        for (int i = 0; i < MAXN; i++) {
            ref[i] = data[i] = uni(rng);
        }
        sort(ref.begin(), ref.end());
        heap_sort(data);
        if (ref != data) {
            puts("?");
            break;
        }
    }
}

void test_heap_pq() {
    default_random_engine rng(random_device{}());
    uniform_int_distribution<> uni{};
    constexpr int MAXN = 100000;
    for (int t = 0; t < 15; t++) {
        priority_queue<int> pq;
        myheap mh;
        for (int i = 0; i < MAXN; i++) {
            int tmp = uni(rng);
            pq.push(tmp);
            mh.push(tmp);
        }
        while (!pq.empty()) {
            if (mh.top() != pq.top()) {
                puts("?");
                break;
            }
            mh.pop();
            pq.pop();
        }
    }
}

int main() {
    test_heap_sort();
    test_heap_pq();
    return 0;
}
