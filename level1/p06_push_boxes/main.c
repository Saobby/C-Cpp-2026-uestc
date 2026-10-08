// 说明:
// 该程序在Linux上测试可用
// 请直接在终端运行该程序构建得到的二进制文件

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

static const int max_map_width = 16;
static const int max_map_height = 16;

int map[16 * 16] = {0};  // 1: 没有 2: 墙壁 3: 箱子 4: 目标点 5: 箱子+目标点
static int player_pos[2] = {0, 0};
static int box_count = 0;
static int placed_box_count = 0;
static int score = 100;

static int get_map(const int x, const int y) {
    if (x < 0 || x >= max_map_width || y < 0 || y >= max_map_height) {
        return 0;
    }
    return map[y * max_map_width + x];
}

static int set_map(const int x, const int y, const int block) {
    if (x < 0 || x >= max_map_width || y < 0 || y >= max_map_height) {
        return 1;
    }
    map[y * max_map_width + x] = block;
    return 0;
}

static int load_map(const char *file_path) {
    FILE *fd = fopen(file_path, "r");
    if (fd == NULL) {
        return -1;
    }
    char line[max_map_width];
    int y = 0;
    while (fgets(line, max_map_width, fd) != NULL) {
        for (int x = 0; x < max_map_width && line[x] != '\n' && line[x] != '\0'; x++) {
            switch (line[x]) {
                case ' ':
                    map[y * max_map_width + x] = 1;  // 空地
                    break;
                case '#':
                    map[y * max_map_width + x] = 2;  // 墙壁
                    break;
                case 'B':
                    map[y * max_map_width + x] = 3;  // 箱子
                    box_count++;
                    break;
                case 'T':
                    map[y * max_map_width + x] = 4;  // 目标点
                    break;
                case 'P':
                    player_pos[0] = x;
                    player_pos[1] = y;
                    map[y * max_map_width + x] = 1;  // 空地
                    break;
                default: ;
            }
        }
        y++;
    }

    return 0;
}

static int move(const int delta_x, const int delta_y) {
    const int new_x = player_pos[0] + delta_x;
    const int new_y = player_pos[1] + delta_y;
    const int block = get_map(new_x, new_y);
    if (block == 1 || block == 4) {  // 前面没东西
        player_pos[0] = new_x;
        player_pos[1] = new_y;
        return 0;
    }
    if (block == 2) {  // 前面是墙壁
        return 1;
    }
    if (block == 3) {  // 前面是箱子
        const int another_x = new_x + delta_x;
        const int another_y = new_y + delta_y;
        const int another_block = get_map(another_x, another_y);
        if (another_block == 1) {  // 箱子前面是空气
            set_map(another_x, another_y, 3);
            set_map(new_x, new_y, 1);
            player_pos[0] = new_x;
            player_pos[1] = new_y;
            return 0;
        }if (another_block == 4) {  // 箱子前面是目标点
            set_map(another_x, another_y, 5);
            set_map(new_x, new_y, 1);
            player_pos[0] = new_x;
            player_pos[1] = new_y;
            placed_box_count++;
            return 0;
        }
        return 1;
    }if (block == 5) {  // 前面是箱子+目标点
        const int another_x = new_x + delta_x;
        const int another_y = new_y + delta_y;
        const int another_block = get_map(another_x, another_y);
        if (another_block == 1) {  // 箱子前面是空气
            set_map(another_x, another_y, 3);
            set_map(new_x, new_y, 4);
            player_pos[0] = new_x;
            player_pos[1] = new_y;
            placed_box_count--;
            return 0;
        }if (another_block == 4) {  // 箱子前面是目标点
            set_map(another_x, another_y, 5);
            set_map(new_x, new_y, 4);
            player_pos[0] = new_x;
            player_pos[1] = new_y;
            return 0;
        }
        return 1;
    }
    return 1;
}

static int print_map() {
    printf("#=墙壁，P=玩家，B=箱子，T=目标点\n");
    printf("WASD控制玩家，将所有箱子推动到目标点\n");
    for (int y = 0; y < max_map_height; y++) {
        for (int x = 0; x < max_map_width; x++) {
            const int block = get_map(x, y);
            if (block == 0) {
                break;
            }
            if (player_pos[0] == x && player_pos[1] == y) {
                printf("P");
                continue;
            }
            switch (block) {
                case 1:
                    printf(" ");
                    break;
                case 2:
                    printf("#");
                    break;
                case 3:
                    printf("B");
                    break;
                case 4:
                    printf("T");
                    break;
                case 5:
                    printf("B");
                    break;
                default: ;
            }
        }
        printf("\n");
    }
    return 0;
}

static char get_input() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

int main() {
    char file_path[64];
    printf("请输入关卡文件路径:");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = '\0';

    srand(time(NULL));

    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    const int res = load_map(file_path);
    if (res == -1) {
        printf("关卡加载失败！！\n");
        return -1;
    }

    int result = -1;
    while (1) {
        system("clear");
        print_map();
        const char input = get_input();
        result = -1;
        if (input == 'w') {
            result = move(0, -1);
        } else if (input == 's') {
            result = move(0, 1);
        } else if (input == 'a') {
            result = move(-1, 0);
        } else if (input == 'd') {
            result = move(1, 0);
        } else if (input == 'q') {
            system("clear");
            printf("游戏已退出！\n");
            break;
        }
        if (result == 0) {
            score--;
        }
        if (placed_box_count == box_count) {
            system("clear");
            printf("你赢了！！！你太棒了！！！你的分数是: %d！赞赞赞！\n", score);
            break;
        }

    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    return 0;
}