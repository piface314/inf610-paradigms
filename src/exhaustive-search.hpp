#ifndef EXHAUSTIVE_SEARCH_H
#define EXHAUSTIVE_SEARCH_H

#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include "data.hpp"
#include "utils.hpp"

namespace xs {

    template <typename T> void permutate(T *v, size_t n, size_t i, std::function<void (T *v, size_t n)> f) {
        if (i == n - 1)
            f(v, n);
        else
            for (size_t j = i; j < n; ++j) {
                std::swap(v[i], v[j]);
                permutate(v, n, i + 1, f);
                std::swap(v[i], v[j]);
            }
    }

    template <typename T> void permutations(T *v, size_t n, std::function<void (T *v, size_t n)> f) {
        xs::permutate(v, n, 0, f);
    }

    template <typename T> void power_set_r(T *v, size_t n, T *b, size_t m, std::function<void (T *v, size_t n)> f) {
        if (n == 0)
            return f(b, m);
        power_set_r(v + 1, n - 1, b, m, f);
        b[m] = *v;
        power_set_r(v + 1, n - 1, b, m + 1, f);
    }

    template <typename T> void power_set(T *v, size_t n, std::function<void (T *v, size_t n)> f) {
        T *buffer = new T[n];
        power_set_r(v, n, buffer, 0, f);
        delete [] buffer;
    }

    std::vector<size_t> traveling_salesman(double *d, size_t n);
    std::vector<size_t> job_scheduling(double *c, size_t n);
    std::vector<size_t> knapsack(int *w, double *v, int w_max, size_t n);
    void test();
}

#endif