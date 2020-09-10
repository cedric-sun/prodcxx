// cesun, 9/8/20 4:28 PM.

// ALL HAIL SAHNI!
#include <vector>
#include <cstdint>
#include <cstring>

#include <cstdio>

using std::vector;

struct loser_tree {
    const int n;
    int *tree;
    int *idx;
    const vector<vector<int>> &tt_lists;

    // PRECONDITION: t_lists.size()>=1 && t_lists[x].size()>=1 for all x
    loser_tree(const vector<vector<int>> &t_lists)
            : n(t_lists.size()), tree(new int[n]), tt_lists(t_lists), idx(new int[n]) {
        memset(idx, 0, sizeof(*idx) * n);
        tree[0] = init(1);
    }

    int init(int i) {// i index into tree
        if (i >= n) {
            return i - n; // index into tt_lists
        }
        // index of left winner and right winner
        int li = init(i << 1), ri = init((i << 1) + 1);
        if (tt_lists[li][0] > tt_lists[ri][0]) {
            tree[i] = li;
            return ri;
        } else {
            tree[i] = ri;
            return li;
        }
    }

#define IALOSE -42

    inline void upfloat(int i) {
        int parent = (i + n) >> 1;
        if (idx[i] >= tt_lists[i].size()) {
            i = IALOSE;
        }
        while (parent > 0) {
            const int j = tree[parent];
            if (j != IALOSE && (i == IALOSE || tt_lists[i][idx[i]] > tt_lists[j][idx[j]]))
                std::swap(tree[parent], i);
            parent >>= 1;
        }
        tree[0] = i;
    }

    int next() {
        const int i = tree[0]; // champion queue index
        int ret = tt_lists[i][idx[i]];
        idx[i]++;
        upfloat(i);
        return ret;
    }

    bool has_next() {
        return tree[0] >= 0;
    }

    virtual ~loser_tree() {
        delete[] tree;
        delete[] idx;
    }
};

//unit test: https://leetcode.com/problems/merge-k-sorted-lists/

/**
 * Definition for singly-linked list.*/
//struct ListNode {
//    int val;
//    ListNode *next;
//
//    ListNode() : val(0), next(nullptr) {}
//
//    ListNode(int x) : val(x), next(nullptr) {}
//
//    ListNode(int x, ListNode *next) : val(x), next(next) {}
//};

class Solution {
public:
    ListNode *mergeKLists(const vector<ListNode *> &lists) {
        if (lists.empty()) {
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
        if (bkb.empty()) {
            return nullptr;
        }
        loser_tree loser{bkb};

        ListNode tmp_head;
        ListNode *cur = &tmp_head;
        while (loser.has_next()) {
            cur = cur->next = new ListNode{loser.next()};
        }
        return tmp_head.next;
    }
};


// -------------------------------------------------------------
#include <stdio_ext.h>

ListNode *make_stupid_linkedlist(vector<int> vec) {
    ListNode tmp_head;
    ListNode *cur = &tmp_head;
    for (const int t : vec) {
        cur = cur->next = new ListNode{t};
    }
    return tmp_head.next;
}

void free_stupid_linkedlist(ListNode *head) {
    while (head != nullptr) {
        ListNode *tmp = head->next;
        delete head;
        head = tmp;
    }
}

void print_stupid_linkedlist(ListNode *head) {
    while (head != nullptr) {
        printf("%d\t", head->val);
        head = head->next;
    }
    putchar('\n');
}

int main() {
    __fsetlocking(stdout, FSETLOCKING_BYCALLER);
    Solution x;
    vector<ListNode *> data = {
            make_stupid_linkedlist({1, 4, 5}),
            make_stupid_linkedlist({1, 3, 4}),
            make_stupid_linkedlist({2, 6})
    };
    ListNode *ans = x.mergeKLists(data);
    print_stupid_linkedlist(ans);
    free_stupid_linkedlist(ans);
    for (ListNode *const p : data) {
        free_stupid_linkedlist(p);
    }
}