//
// Created by stguable on 2026/10/21.
//

#include "is_prime.h"
#include <math.h>

int is_prime(const int n) {
    if (n < 2) {
        return 0; // Not prime
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return 0; // Not prime
        }
    }
    return 1; // Prime
}
