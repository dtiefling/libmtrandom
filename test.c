#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define N 100000000
#define MIN(a, b) (a < b ? a : b)

int main() {
    static int arr[N];
    clock_t c0, c1;
    int i;

    srand(time(NULL));

    c0 = clock();
    for(i = 0; i < N; ++i) {
        arr[i] = rand();
    }
    c1 = clock();

    printf("Time: %.3f\n", (c1 - c0) / (double)(CLOCKS_PER_SEC));

    for(i = 0; i < MIN(N, 100); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
