// cesun, 9/8/20 4:28 PM.

// ALL HAIL SAHNI!
#include <vector>
#include <cstring>

using std::vector;

#ifdef __LOCAL_RUN__
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#endif

struct loser_tree {
    const int n;
    int *const tree;

    vector<const ListNode *> &vec;

    // PRECONDITION: t_lists.size()>=1 && t_lists[x].size()>=1 for all x
    loser_tree(vector<const ListNode *> &vvec) : n(vvec.size()), tree(new int[n]), vec(vvec) {
        tree[0] = init(1);
    }

    int init(int i) {// i index into tree
        if (i >= n) return i - n;
        int li = init(i << 1), ri = init((i << 1) + 1);
        if (vec[li]->val > vec[ri]->val) {
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
        if (vec[i] == nullptr) {
            i = IALOSE;
        }
        while (parent > 0) {
            const int j = tree[parent];
            if (j != IALOSE && (i == IALOSE || vec[i]->val > vec[j]->val))
                std::swap(tree[parent], i);
            parent >>= 1;
        }
        tree[0] = i;
    }

    int next() {
        const int i = tree[0]; // champion queue index
        int ret = vec[i]->val;
        vec[i] = vec[i]->next;
        upfloat(i);
        return ret;
    }

    bool has_next() {
        return tree[0] >= 0;
    }

    virtual ~loser_tree() {
        delete[] tree;
    }
};

//unit test: https://leetcode.com/problems/merge-k-sorted-lists/


class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;
        vector<const ListNode *> sanitized;
        sanitized.reserve(lists.size());
        for (const ListNode *const &x : lists) {
            if (x != nullptr) {
                sanitized.push_back(x);
            }
        }
        if (sanitized.empty()) return nullptr;

        loser_tree loser{sanitized};
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

void free_stupid_linkedlist(const ListNode *head) {
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
    for (const ListNode *const p : data) {
        free_stupid_linkedlist(p);
    }
}