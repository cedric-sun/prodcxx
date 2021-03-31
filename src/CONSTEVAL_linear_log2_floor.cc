// cesun, 9/6/20 11:41 PM.

#define LOG2_FLOOR_N 10000

consteval int *init_floor_log2() {
    int *log2_floor = new int[LOG2_FLOOR_N + 1];
    log2_floor[1] = 0;
    for (int i = 2; i <= LOG2_FLOOR_N; i++)
        log2_floor[i] = log2_floor[i >> 1] + 1;
    return log2_floor;
}

static constinit int *log2_floor = init_floor_log2();

#include <cstdio>

int main() {
    printf("%d\n", log2_floor[3005])
}
