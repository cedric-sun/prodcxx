// cesun, 9/29/20 2:13 AM.

// a fancy solution of the exact subset sum using hash set just for fun
// the size of `gen` and `s` will still grow exponentially and fill [0,capacity]

// In reality it's much much slower than the original version.

#include <algorithm>
#include <unordered_set>

namespace improve1 {
    bool knapsack(const int *items, const int item_n, const int capacity) {
        std::unordered_set<int> s;
        std::vector<int> gen;
        s.reserve(capacity); // space complexity is still there...
        gen.reserve(capacity);
        s.insert(0);
        gen.push_back(0);
        for (int i = 0; i < item_n; ++i) {
            const int genCurSize = gen.size();
            for (int j = 0; j < genCurSize; ++j) {
                const int newWeight = gen[j] + items[i]; // TODO: ensure no int overflow
                if (newWeight > capacity)
                    continue;
                if (newWeight == capacity)
                    return true;
                if (s.find(newWeight) == s.cend()) {
                    gen.push_back(newWeight);
                    s.insert(newWeight);
                }
            }
        }
        return false;
    }
}
