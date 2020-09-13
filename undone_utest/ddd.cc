// cesun, 9/7/20 7:54 PM.

https://www.spoj.com/problems/CHAIN/
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

int main() {
    int t, n, k;
    scanf("%d\n", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        disjoint_set ds{n + 1};
        std::unordered_map<int, std::unordered_set<int>> predation;
        int n_false = 0;
        while (k--) {
            int d, x, y;
            scanf("%d %d %d", &d, &x, &y);
            if (x > n || y > n) {
                n_false++;
                continue;
            }
            if (d == 1) { // x and y are same
                const auto a_eat_b = [predation](const int a, const int b) {
                    const auto it = predation.find(a);
                    return it != predation.end() && it->second.find(b) != it->second.cend();
                };
                if (a_eat_b(x, y) || a_eat_b(y, x)) {
                    n_false++;
                    continue;
                }
                ds.join(x, y);
            } else { // x can eat y
                int a = ds.find(x), b = ds.find(y);
                if (a == b) {
                    n_false++;
                    continue;
                }
                predation[x].insert(y);
            }
        }
        printf("%d\n", n_false);
    }
}