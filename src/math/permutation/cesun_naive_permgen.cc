#include <bits/stdc++.h>
using namespace std;

bool used[6];

// lc46
class Solution {
public:
    vector<vector<int>> ans;
    vector<int> cur;

    void dfs(const int i, const vector<int> &nums) {
        if (i == nums.size()) {
            ans.push_back(cur);
            return;
        }
        for (int j = 0; j < nums.size(); ++j) {
            if (!used[j]) {
                cur[i] = nums[j];
                used[j] = true;
                dfs(i + 1, nums);
                used[j] = false;
            }
        }
    }

    vector<vector<int>> permute(vector<int> &nums) {
        memset(used, 0, sizeof used);
        cur.resize(nums.size());
        dfs(0, nums);
        return ans;
    }
};

