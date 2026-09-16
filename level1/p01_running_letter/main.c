#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char text[] = "hello world!";

    while (1) {
        for (int n = 0; n < 20; n++) {
            system("clear");
            for (int i = 0; i < n; i++) {
                printf(" ");

            }
            printf("%s\n", text);
            usleep(100000);
        }

        for (int n = 18; n >= 1; n--) {
            system("clear");
            for (int i = 0; i < n; i++) {
                printf(" ");

            }
            printf("%s\n", text);
            usleep(100000);
        }
    }



    return 0;
}