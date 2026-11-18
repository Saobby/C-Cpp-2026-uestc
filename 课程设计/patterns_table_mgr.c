//
// Created by stguable on 2026/11/18.
//

#include "patterns_table_mgr.h"
#include <stdio.h>
#include <math.h>

int get_blk_type(const int idx, const int pos) {
    return (idx % (1 << ((pos + 1) * 2))) >> (pos * 2);
}

int is_sub_array(const int * big_array, const int big_len, const int * small_array, const int small_len) {
    for (int offset = 0; offset <= big_len - small_len; offset++) {
        int ok = 1;
        for (int i = 0; i < small_len; i++) {
            if (big_array[offset + i] != small_array[i]) {
                ok = 0;
                break;
            }
        }
        if (ok == 1) {
            return offset;
        }
    }
    return -1;
}

void gen_patterns_table(Table * table) {
    for (int i = 0; i < PATTERNS_TABLE_SIZE; i++) {
        table->table[i] = 0;
        table->offset[i] = 0;
    }
    const int * patterns[] = {
        (int[]){0, 1, 1, 1, 1, 0},  // 活4
        (int[]){0, 1, 1, 0, 1, 0},  // 跳3正
        (int[]){0, 1, 0, 1, 1, 0},  // 跳3反
        (int[]){1, 1, 1, 1, 1},  // 连5
        (int[]){1, 1, 1, 1, 0},  // 冲4_1正
        (int[]){0, 1, 1, 1, 1},  // 冲4_1反
        (int[]){1, 1, 1, 0, 1},  // 冲4_2正
        (int[]){1, 0, 1, 1, 1},  // 冲4_2反
        (int[]){1, 1, 0, 1, 1},  // 冲4_3
        (int[]){0, 1, 1, 1, 0},  // 活3
        (int[]){0, 1, 1, 0, 0},   // 活2_正
        (int[]){0, 0, 1, 1, 0}   // 活2_反
    };
    const int patterns_len[] = {6, 6, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    const int patterns_type[] = {1, 2, 2, 3, 4, 4, 4, 4, 4, 5, 6, 6};
    // 0: 空气  1: 我方子  2: 敌方子
    for (int i = 0; i < 262144; i++) {
        int curr_pattern[9];
        int has3 = 0;
        for (int j = 0; j < 9; j++) {
            const int t = get_blk_type(i, j);
            if (t == 3) {
                has3 = 1;
                break;
            }
            curr_pattern[j] = t;
        }
        if (has3) {
            continue;
        }
        int idx = 0;
        for (int m = 0; m < 9; m++) {
            idx += (int)pow(3, m) * curr_pattern[m];
        }
        for (int k = 0; k < 12; k++) {
            // 遍历所有模式
            const int * pattern = patterns[k];
            const int pattern_len = patterns_len[k];
            const int pattern_type = patterns_type[k];
            const int offset = is_sub_array(curr_pattern, 9, pattern, pattern_len);
            if (offset == -1) {
                continue;
            }
            table->table[idx] = pattern_type;
            table->offset[idx] = offset;
            break;
        }
    }
}

int save_patterns_table() {
    Table table;
    gen_patterns_table(&table);
    FILE * fp = fopen("patterns.txt", "w");
    if (fp == NULL) {
        return -1;
    }
    for (int i = 0; i < PATTERNS_TABLE_SIZE; i++) {
        fputc(table.table[i] + '0', fp);
        fputc(table.offset[i] + '0', fp);
    }
    fclose(fp);
    return 0;
}

int load_patterns_table(Table * table) {
    const FILE * fp = fopen("patterns.txt", "r");
    if (fp == NULL) {
        return -1;
    }
    int t;
    int i = 0;
    while ((t = fgetc(fp)) != EOF) {
        if (i % 2 == 0) {
            table->table[i / 2] = t - '0';
        }else {
            table->offset[i / 2] = t - '0';
        }
        i++;
    }
    return 0;
}
