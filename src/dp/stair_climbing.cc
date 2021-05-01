#include <bits/stdc++.h>

using namespace std;

// all the variants of the innocent stair climbing problem

// climbing stairs problem represents a general type of problem of "find the unique ways to do something".
// This type problem usually never ask you to print all plans, since the total number of plans or distinct ways
// are too huge (consider fib sequence).
// See also:    https://leetcode.com/problems/unique-paths/     (2d variants)
//              https://leetcode.com/problems/decode-ways/      (more complicated state transferring rules)

namespace base {
    // 1 or 2 treads each step, find # of ways to step on the n-th tread
    // https://leetcode.com/problems/climbing-stairs/

    uint64_t memo[45]; // memo[i] is f(i+1)

    auto init_memo = []() {
        memo[0] = 1;
        memo[1] = 2;
        for (int i = 2; i < 45; i++)
            memo[i] = memo[i - 1] + memo[i - 2];
        return nullptr;
    }();

    class Solution {
    public:
        int climbStairs(int n) { return memo[n - 1]; }
    };
}

namespace cannot_consecutive_2_step {
    // 字节2020.9.6
    // 1 or 2 tread each step, but can't take consecutive steps of 2,
    // find # of ways to step on the n-th tread

    // Solution:
    // denote f_1(i) the # of ways to step on the i-th tread by taking 1 tread from i-1;
    // denote f_2(i) the # of ways to step on the i-th tread by taking 2 treads from i-2;
    // denote f(i) the # of ways to step on the i-th tread anyway;
    // We have
    // 1. f(i) = f_1(i) + f_2(i)
    // it's always okay to take step of 1 tread, so the # of ways to step on the i-th treads by stepping 1 is exactly
    // the same as that of the previous tread
    // 2. f_1(i) = f(i-1) = f_1(i-1) + f_2(i-1)
    // taking step of 2 treads is only okay when
    // 3. f_2(i) = f_1(i-2)
    int cannot_consecutive_2_step(const int n) {
        vector<int> f1(n + 1), f2(n + 1);
        // idx  0   1   2   3
        // f1   1   1   1   ...
        // f2   /   0   1   ...
        f1[1] = 1;
        f1[2] = 1;
        f2[2] = 1;
        // or f1[0] = 1, f1[1] = 1, f2[1] = 0, and i start from 2
        for (int i = 3; i <= n; i++) {
            f1[i] = f1[i - 1] + f2[i - 1];
            f2[i] = f1[i - 2];
        }
        return f1[n] + f2[n];
    }
}

namespace runtime_step_allowed {
    // same as the classic one but instead of stepping 1 or 2, the set of allowed steps
    // are passed in as a runtime collection `steps`;
    // f[0] = 1
    // f[i] = sum(f[i-j]) for all j in s and i-j>=0;
    int runtime_step_allowed(const int n, vector<int> steps) {
        // we can optimize to a vector of size max(steps) if only 1 query,
        // since that's the max number of state we need to remember;
        vector<int> f(n + 1);
        f[0] = 1;
        sort(steps.begin(), steps.end()); // be friendly to the branch predictor; not mandatory
        for (int i = 1; i <= n; i++) {
            for (int s : steps) {
                if (i - s >= 0) {
                    f[i] += f[i - s];
                }
            }
        }
        return f[n];
    }
}

int main() {
    cout << cannot_consecutive_2_step::cannot_consecutive_2_step(14) << endl;
    cout << runtime_step_allowed::runtime_step_allowed(6, {2, 3, 5}) << endl;
}