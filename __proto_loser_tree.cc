// cesun, 9/8/20 4:28 PM.

// ALL HAIL SAHNI!
#include <vector>
#include <cstdint>
#include <cstring>

using std::vector;

struct loser_tree {
    const int n;
    int *tree;
    bool *lr;
    int *idx;
    const vector<vector<int>> &tt_lists;

#define LEFT true
#define RIGHT false

    loser_tree(const vector<vector<int>> &t_lists)
            : n(t_lists.size()), tree(new int[n]), lr(new bool[n]),
              tt_lists(t_lists), idx(new int[n]) {
        memset(tree, -1, sizeof(*tree) * n);
        memset(lr, 0, sizeof(*lr) * n);
        memset(idx, 0, sizeof(*idx) * n);
        init_play(1);
    }

    inline int feed_from(int j) {
        if (idx[j] >= tt_lists[j].size()) {
            //TODO need a way to tell queue j reach its end
        }
        int ret = tt_lists[j][idx[j]];
        ++idx[j];
        return ret;
    }

    int init_play(int i) {
        if (i > n) {
            const int j = i - n - 1;
            return feed_from(j);
        }
        int lw = init_play(i << 1), rw = init_play((i << 1) + 1);
        if (lw > rw) {
            tree[i] = lw;
            lr[i] = LEFT;
            return rw;
        } else {
            tree[i] = rw;
            lr[i] = RIGHT;
            return lw;
        }
    }

    int replay(int i) {
        if (i > n) {
            const int j = i - n - 1;
            return feed_from(j);
        }
        int bot_winner;
        bot_winner = replay(lr[i] == LEFT ? (i << 1) + 1 : i << 1);
        if (bot_winner > tree[i]) {
            int tmp = tree[i];
            tree[i] = bot_winner;
            lr[i] = !lr[i];
            return tmp;
        } else {
            return bot_winner;
        }
    }

    int next() {
        return replay(1);
    }

    bool has_next() {
        //TODO need a way to tell when all data is spat out
        return false;
    }

    virtual ~loser_tree() {
        delete[] tree;
        delete[] lr;
        delete[] idx;
    }
};

//unit test: https://leetcode.com/problems/merge-k-sorted-lists/

/**
 * Definition for singly-linked list.*/
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeKLists(const vector<ListNode *> &lists) {
        if (lists.size() == 0) {
            return nullptr;
        }
        vector<vector<int>> bkb;
        vector<int> tmp;
        for (const ListNode *p : lists) {
            tmp.clear();
            while (p != nullptr) {
                tmp.push_back(p->val);
                p = p->next;
            }
            if (!tmp.empty()) {
                bkb.push_back(std::move(tmp));
            }
        }
        loser_tree loser{bkb};
        ListNode *head, *cur;
        cur = head = new ListNode;
        while (loser.has_next()) {
            cur = cur->next = new ListNode{loser.next()};
        }
        return head->next;
    }
};