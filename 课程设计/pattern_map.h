//
// Created by stguable on 2026/11/4.
//

#ifndef CCPP2026_PATTERN_MAP_H
#define CCPP2026_PATTERN_MAP_H
#include "evaluator.h"

typedef struct PatternMap {
    FindBasicPatternResult pattern_map[512];
}PatternMap;

PatternMap * create_pattern_map();

PatternMap * save_pattern(PatternMap * pattern_map, int stone_type, FindBasicPatternResult pattern);

FindBasicPatternResult find_pattern(const PatternMap * pattern_map, int stone_type, int x, int y);

#endif //CCPP2026_PATTERN_MAP_H
