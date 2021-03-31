// cesun, 9/7/20 2:41 PM.

// merge by size, path compression, memset init

#include <cstring>

static int ds[MAXN];
static int nset; // number of separated sets;

// index is [0,n)
static void ds_init(int n) {
    nset = n;
    memset(ds, -1, sizeof(*ds) * n);
}

static int ds_find(int x) {
    // n=2^63 to overflow this buffer
    static int stack[64], top = 0;
    while (ds[x] >= 0) {
        stack[top++] = x;
        x = ds[x];
    }
    while (top) ds[stack[--top]] = x;
    return x;
}

//PRECONDITION: a = find(x); b=find(y); a != b
static void ds_join_leader(const int a, const int b) {
    if (ds[a] <= ds[b]) {
        ds[a] += ds[b];
        ds[b] = a;
    } else {
        ds[b] += ds[a];
        ds[a] = b;
    }
    --nset;
}

static void ds_join(const int x, const int y) {
    const int a = ds_find(x), b = ds_find(y);
    if (a != b) {
        ds_join_leader(a, b);
    }
}