#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int maze_size = 9;

int randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int *get_dot_edges(int dot_idx) {
    int offset = (maze_size - 1) * maze_size;
    int x = dot_idx % maze_size;
    int y = dot_idx / maze_size;
    int *edge_and_dot_ids = malloc(8 * sizeof(int));
    edge_and_dot_ids[0] = -1;
    edge_and_dot_ids[1] = -1;
    edge_and_dot_ids[2] = -1;
    edge_and_dot_ids[3] = -1;
    edge_and_dot_ids[4] = -1;
    edge_and_dot_ids[5] = -1;
    edge_and_dot_ids[6] = -1;
    edge_and_dot_ids[7] = -1;
    // edge_id: 前一部分:横着的边，后一部分:竖着的边
    if (x > 0) {  // 左
        edge_and_dot_ids[0] = y * (maze_size - 1) + (x - 1);
        edge_and_dot_ids[4] = y * maze_size + (x - 1);
    }
    if (x < maze_size - 1) {  // 右
        edge_and_dot_ids[1] = y * (maze_size - 1) + x;
        edge_and_dot_ids[5] = y * maze_size + x + 1;
    }
    if (y > 0) {  // 上
        edge_and_dot_ids[2] = x * (maze_size - 1) + (y - 1) + offset;
        edge_and_dot_ids[6] = (y - 1) * maze_size + x;
    }
    if (y < maze_size - 1) {  // 下
        edge_and_dot_ids[3] = x * (maze_size - 1) + y + offset;
        edge_and_dot_ids[7] = (y + 1) * maze_size + x;
    }

    return edge_and_dot_ids;
}

int *gen_maze() {
    int offset = (maze_size - 1) * maze_size;
    int *maze = malloc((maze_size*2+1) * (maze_size*2+1) * sizeof(int));
    int edges[(maze_size - 1) * maze_size * 2];
    int edge_weights[(maze_size - 1) * maze_size * 2];
    for (int i = 0; i < (maze_size - 1) * maze_size * 2; i++) {
        edges[i] = 0;
        edge_weights[i] = randint(0, 9999);
    }
    int dots[maze_size * maze_size];
    for (int i = 0; i < maze_size * maze_size; i++) {
        dots[i] = 0;
    }
    dots[0] = 1;

    for (int n = 0; n < maze_size * maze_size - 1; n++) {
        int min_weight = 10000;
        int min_weight_edge_idx = -1;
        int min_weight_edge_dot_idx = -1;
        for (int i = 0; i < maze_size * maze_size; i++) {
            if (dots[i] == 1) {
                int *edge_and_dots = get_dot_edges(i);
                for (int j = 0; j < 4; j++) {
                    if (edges[edge_and_dots[j]] == 0 && dots[edge_and_dots[j+4]] == 0) {
                        if (edge_weights[edge_and_dots[j]] < min_weight) {
                            min_weight = edge_weights[edge_and_dots[j]];
                            min_weight_edge_idx = edge_and_dots[j];
                            min_weight_edge_dot_idx = edge_and_dots[j+4];
                        }
                    }
                }
            }
        }
        edges[min_weight_edge_idx] = 1;
        dots[min_weight_edge_dot_idx] = 1;
    }

    for (int i = 0; i < (maze_size*2+1) * (maze_size*2+1); i++) {
        maze[i] = 1;
    }

    for (int x = 0; x < maze_size; x++) {
        for (int y = 0; y < maze_size; y++) {
            maze[(y*2+1)*(maze_size*2+1)+x*2+1] = 0;
        }
    }

    for (int x = 0; x < (maze_size - 1); x++) {
        for (int y = 0; y < maze_size; y++) {
            int edge_idx = y * (maze_size - 1) + x;
            if (edges[edge_idx] == 1) {
                int x_ = 2 * (x+1);
                int y_ = 2 * y + 1;
                maze[y_ * (maze_size * 2 + 1) + x_] = 0;
            }
        }
    }

    for (int x = 0; x < (maze_size - 1); x++) {
        for (int y = 0; y < maze_size; y++) {
            int edge_idx = y * (maze_size - 1) + x;
            if (edges[edge_idx+offset] == 1) {
                int x_ = 2 * y + 1;
                int y_ = 2 * (x+1);
                maze[y_ * (maze_size * 2 + 1) + x_] = 0;
            }
        }
    }

    return maze;
}

int main() {
    srand(time(NULL));

    int *maze = gen_maze();

    for (int y = 0; y < maze_size * 2 + 1; y++) {
        for (int x = 0; x < maze_size * 2 + 1; x++) {
            int idx = y * (maze_size * 2 + 1) + x;
            if (maze[idx] == 1) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}