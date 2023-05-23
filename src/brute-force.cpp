#include "brute-force.hpp"

void bf::select_sort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i) {
        int m = i;
        for (size_t j = i + 1; j < n; ++j)
            if (a[j] < a[m])
                m = j;
        swap(a[i], a[m]);
    }
}

void bf::bubble_sort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 1; j < n - i; ++j)
            if (a[j-1] > a[j])
                swap(a[j-1], a[j]);
}

int bf::seq_search(int k, int *a, size_t n) {
    for (size_t i = 0; i < n; ++i)
        if (a[i] == k)
            return i;
    return -1;
}

int bf::str_match(char *text, size_t n, char *pattern, size_t m) {
    for (size_t i = 0; i < n - m; ++i) {
        size_t j;
        for (j = 0; j < m && text[i+j] == pattern[j]; ++j);
        if (j == m)
            return i;
    }
    return -1;
}

std::pair<int, Range> bf::max_subseq_sum(int *a, size_t n) {
    int m = 0;
    Range r { i: 0, j: 0 };
    for (size_t i = 0; i < n; ++i) {
        int s = 0;
        for (size_t j = i; j < n; ++j) {
            s += a[j];
            if (s > m) {
                m = s;
                r.i = i, r.j = j;
            }
        }
    }
    return std::pair(m, r);
}

std::pair<size_t, size_t> bf::closest_pair(Point *p, size_t n) {
    double d_min = std::numeric_limits<double>::max();
    std::pair<size_t, size_t> pair;
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = i + 1; j < n; ++j) {
            double d = p[i].distance(p[j]);
            if (d < d_min)
                pair = {i, j}, d_min = d;
        }
    return pair;
}

std::pair<Point*, size_t> bf::convex_hull(Point *p, size_t n) {
    bool in_hull[n] = {0};
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            Line l { p[i], p[j] };
            double side = 0;
            size_t k;
            for (k = 0; k < n; ++k) {
                if (k == i || k == j)
                    continue;
                double s = l.side(p[k]);
                if (side == 0)
                    side = s;
                else if (side * s < 0)
                    break;
            }
            if (k == n)
                in_hull[i] = true, in_hull[j] = true;
        }
    }

    size_t h = 0, k = 0;
    for (size_t i = 0; i < n; ++i)
        h += in_hull[i];
    Point *hull = new Point[h];
    for (size_t i = 0; i < n; ++i)
        if (in_hull[i])
            hull[k++] = p[i];
    return {hull, h};
}
