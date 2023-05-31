#ifndef DYNAMIC_PROG_H
#define DYNAMIC_PROG_H

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "data.hpp"
#include "utils.hpp"

namespace dp {
    std::pair<int, std::vector<int>> coin_row(int *c, size_t n);
    std::vector<int> change_making(int n, int *c, size_t m);
    std::pair<int, std::vector<std::pair<size_t,size_t>>> coin_collecting(bool *c, size_t m, size_t n);
    std::pair<int, Range> max_subseq_sum(int *a, size_t n);
    std::vector<size_t> knapsack(int *w, double *v, int w_max, size_t n);
    bool *transitive_closure(bool *adj, size_t n);
    int *all_pairs_shortest_pairs(int *w, size_t n);
    void test();
}

#endif