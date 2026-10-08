#include <stdio.h>
#include <math.h>
#include <time.h>

int is_prime(int my_num) {
    for (int i = 2; i <= sqrt(my_num); i++) {
        if (my_num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i=2; i<=1000; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("%.6f s\n", elapsed);
    return 0;
}