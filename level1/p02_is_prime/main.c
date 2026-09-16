#include <stdio.h>
#include <math.h>

int main() {
    int my_num;
    printf("Enter a number: ");
    scanf("%d", &my_num);

    int is_prime = 1;

    for (int i = 2; i <= sqrt(my_num); i++) {
        if (my_num % i == 0) {
            is_prime = 0;
            break;
        }
    }

    if (is_prime) {
        printf("%d is a prime number.\n", my_num);
    } else {
        printf("%d is not a prime number.\n", my_num);
    }

    return 0;
}