//
// Created by adamc on 03.12.2023.
//

#ifndef PEA2_CMP_H
#define PEA2_CMP_H

#endif //PEA2_CMP_H

#include <utility>

struct Cmp {
    bool operator()(const std::pair<int, std::pair<int, int>>& a, const std::pair<int, std::pair<int, int>>& b) const {
        return a.first > b.first; // Compare by the first element for min-heap
    }
};