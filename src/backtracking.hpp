#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "data.hpp"
#include "utils.hpp"

namespace bt {
    std::vector<size_t> n_queens(size_t n);
    std::vector<std::vector<int>> subset_sum(int m, int *w, size_t n);
    void test();
}

#endif