#include <stdio.h>

int move_hanoi(int height, char from, char dest, char temp) {
    if (height == 1) {
        printf("%c -> %c\n", from, dest);
    }else {
        move_hanoi(height-1, from, temp, dest);
        move_hanoi(1, from, dest, temp);
        move_hanoi(height-1, temp, dest, from);
    }
    return 0;
}

int main() {
    move_hanoi(4, 'A', 'C', 'B');
    return 0;
}
