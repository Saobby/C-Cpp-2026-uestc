#include <stdio.h>
#include "is_prime.h"

int main() {
    int my_num;
    printf("Enter a number: ");
    scanf("%d", &my_num);

    const int result = is_prime(my_num);

    if (result) {
        printf("%d is a prime number.\n", my_num);
    } else {
        printf("%d is not a prime number.\n", my_num);
    }

    return 0;
}