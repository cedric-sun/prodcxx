// cesun, 9/6/20 11:41 PM.

#define LOG2_FLOOR_N 100

static int floor_log2[LOG2_FLOOR_N + 1];

static void init_floor_log2() {
    floor_log2[1] = 0;
    for (int i = 2; i <= LOG2_FLOOR_N; i++)
        floor_log2[i] = floor_log2[i >> 1] + 1;
}