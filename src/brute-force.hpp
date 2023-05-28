#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <iostream>
#include <limits>
#include <vector>
#include "data.hpp"
#include "utils.hpp"

namespace bf {
    void select_sort(int *a, size_t n);
    void bubble_sort(int *a, size_t n);
    int seq_search(int k, int *a, size_t n);
    int str_match(char *text, size_t n, char *pattern, size_t m);
    std::pair<int, Range> max_subseq_sum(int *a, size_t n);
    std::vector<Point> convex_hull(Point *p, size_t n);
    std::pair<Point, Point> closest_pair(Point *p, size_t n);
    void test();
}

#endif