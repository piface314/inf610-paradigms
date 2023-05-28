#ifndef DIVIDE_CONQUER_H
#define DIVIDE_CONQUER_H

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "data.hpp"
#include "utils.hpp"

namespace dc {
    size_t binary_search(int k, int *x, size_t n);
    void quicksort(int *x, size_t n);
    void mergesort(int *x, size_t n);
    std::vector<Point> convex_hull(Point *p, size_t n);
    std::pair<Point, Point> closest_pair(Point *p, size_t n);
    std::pair<int, Range> max_subseq_sum(int *a, size_t n);
    void test();
}

#endif