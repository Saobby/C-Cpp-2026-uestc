//
// Created by stguable on 2026/11/4.
//

#include "pattern_map.h"

#include <stdlib.h>


PatternMap * create_pattern_map() {
    PatternMap * pattern_map = malloc(sizeof(PatternMap));
    for (int i = 0; i < 512; i++) {
        FindBasicPatternResult pattern;
        pattern.pattern_type = 0;
        pattern_map->pattern_map[i] = pattern;
    }
    return pattern_map;
}


PatternMap * save_pattern(PatternMap * pattern_map, const int stone_type, const FindBasicPatternResult pattern) {
    // stone_type: 0: 黑  1: 白
    const int idx = (stone_type << 8) + (pattern.stone_pos[0][0] << 4) + pattern.stone_pos[0][1];
    pattern_map->pattern_map[idx] = pattern;
    return pattern_map;
}


FindBasicPatternResult find_pattern(const PatternMap * pattern_map, const int stone_type, const int x, const int y) {
    // stone_type: 0: 黑  1: 白
    const int idx = (stone_type << 8) + (x << 4) + y;
    return pattern_map->pattern_map[idx];
}
