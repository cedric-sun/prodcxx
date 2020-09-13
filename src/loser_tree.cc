// cesun, 9/8/20 4:28 PM.

/**
 * TODO: formalize type T to be a pair of iterator and its cend.
 */

/**
 *          plot twist: loser tree is heap keyed on the head of each queue.
 *                  you pop the top of the heap, if
 *                      1. the popped queue has more elements, you replace top with that next element and sift down
 *                      2. the popped queue has no more element, you sift up the last queue in the heap array.
 *                  even just using the priority_queue from stl is not too bad, you just pop and push again
 *                      which is just a constant factor slower.
 *          min fibonacci heap could decrease key in O(1), but after we pop the top,
 *                 we need to increase key.
*/
#include <vector>

using std::vector;

template<typename T>
struct loser_tree {
    const int n;
    int *const tree;
    vector<T> &vec;

    // PRECONDITION: t_lists.size()>=1 && t_lists[x].size()>=1 for all x
    loser_tree(vector<T> &vvec) : n(vvec.size()), tree(new int[n]), vec(vvec) {
        tree[0] = init(1);
    }

    int init(int i) {// i index into tree
        if (i >= n) return i - n;
        int li = init(i << 1), ri = init((i << 1) + 1);
        if (vec[li] > vec[ri]) {
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
        if (vec[i].invalid()) i = IALOSE;
        while (parent > 0) {
            const int j = tree[parent];
            if (j != IALOSE && (i == IALOSE || vec[i] > vec[j]))
                std::swap(tree[parent], i);
            parent >>= 1;
        }
        tree[0] = i;
    }

    int next() {
        const int i = tree[0]; // champion queue index
        int ret = vec[i].value();
        vec[i].next();
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
#ifdef __LOCAL_RUN__

#include "misc/listnode.h"

#endif

struct ListNodeWrapper {
    ListNode *p;

    explicit ListNodeWrapper(ListNode *p) : p(p) {}

    bool operator>(const ListNodeWrapper &o) {
        return p->val > o.p->val;
    }

    bool invalid() {
        return p == nullptr;
    }

    void next() {
        p = p->next;
    }

    int value() {
        return p->val;
    }
};

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return nullptr;
        vector<ListNodeWrapper> sanitized;
        sanitized.reserve(lists.size());
        for (ListNode *x : lists)
            if (x != nullptr)
                sanitized.emplace_back(x);
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