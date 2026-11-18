//
// Created by stguable on 2026/11/18.
//

#ifndef CCPP2026_PATTERNS_TABLE_MGR_H
#define CCPP2026_PATTERNS_TABLE_MGR_H

#define PATTERNS_TABLE_SIZE 19683

typedef struct Table {
    int table[PATTERNS_TABLE_SIZE];  // 3^9
}Table;

int get_blk_type(int idx, int pos);

void gen_patterns_table(Table * table);

int save_patterns_table();

int load_patterns_table(Table * table);

#endif //CCPP2026_PATTERNS_TABLE_MGR_H
