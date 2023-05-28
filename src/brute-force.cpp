#include "brute-force.hpp"

void bf::select_sort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i) {
        int m = i;
        for (size_t j = i + 1; j < n; ++j)
            if (a[j] < a[m])
                m = j;
        std::swap(a[i], a[m]);
    }
}

void bf::bubble_sort(int *a, size_t n) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 1; j < n - i; ++j)
            if (a[j-1] > a[j])
                std::swap(a[j-1], a[j]);
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

std::pair<Point, Point> bf::closest_pair(Point *p, size_t n) {
    double d_min = std::numeric_limits<double>::max();
    std::pair<size_t, size_t> pair;
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = i + 1; j < n; ++j) {
            double d = p[i].distance(p[j]);
            if (d < d_min)
                pair = {i, j}, d_min = d;
        }
    return std::pair(p[pair.first], p[pair.second]);
}

std::vector<Point> bf::convex_hull(Point *p, size_t n) {
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
    std::vector<Point> hull;
    for (size_t i = 0; i < n; ++i)
        if (in_hull[i])
            hull.push_back(p[i]);
    return hull;
}


void bf::test() {
    std::cout << "=== Brute Force ===\n";
    std::cout << "Select Sort\n";
    int a1[] = {3, 1, 4, 1, 5, 9, 2, 6};
    PRINT_A(a1, sizeof(a1) / sizeof(int));
    bf::select_sort(a1, sizeof(a1) / sizeof(int));
    PRINT_A(a1, sizeof(a1) / sizeof(int));
    std::cout << "\n";

    std::cout << "Bubble Sort\n";
    int a2[] = {3, 1, 4, 1, 5, 9, 2, 6};
    PRINT_A(a2, sizeof(a2) / sizeof(int));
    bf::bubble_sort(a2, sizeof(a2) / sizeof(int));
    PRINT_A(a2, sizeof(a2) / sizeof(int));
    std::cout << "\n";
    
    std::cout << "Sequential Search\n";
    PRINT_A(a2, sizeof(a2) / sizeof(int));
    std::cout << "2? @" << bf::seq_search(2, a2, sizeof(a2) / sizeof(int)) << "\n";
    std::cout << "10? @" << bf::seq_search(10, a2, sizeof(a2) / sizeof(int)) << "\n";
    std::cout << "\n";

    std::cout << "String Match\n";
    char text[] = "nobody noticed him";
    char pattern[] = "not";
    std::cout << "text:    " << text << "\n";
    std::cout << "pattern: " << pattern << "\n";
    std::cout << bf::str_match(text, sizeof(text)/sizeof(char)-1, pattern, sizeof(pattern)/sizeof(char)-1) << "\n";
    std::cout << "\n";

    std::cout << "Maximum Subsequence Sum (MSS)\n";
    int a3[] = {4, 2, -7, 3, 0, -2, 1, 5, -2};
    PRINT_A(a3, sizeof(a3) / sizeof(int));
    auto mss = bf::max_subseq_sum(a3, sizeof(a3) / sizeof(int));
    std::cout << mss.first << " @ " << mss.second << "\n";
    int a4[] = {-2, 11, -4, 13, -5, 2};
    PRINT_A(a4, sizeof(a4) / sizeof(int));
    auto mss2 = bf::max_subseq_sum(a4, sizeof(a4) / sizeof(int));
    std::cout << mss2.first << " @ " << mss2.second << "\n";
    std::cout << "\n";

    std::cout << "Closest Pair\n";
    Point p1[] = {{1, 2}, {0, -4}, {3, 2}, {-2, 3}, {-1, -1}};
    PRINT_A(p1, sizeof(p1) / sizeof(Point));
    auto cp = bf::closest_pair(p1, sizeof(p1) / sizeof(Point));
    std::cout << cp.first << " ~ " << cp.second << ": " << cp.first.distance(cp.second) << "\n";
    std::cout << "\n";

    std::cout << "Convex Hull\n";
    Point p2[] = {{0, 0}, {-1, -2}, {1, 0}, {-2, 1}, {0, 1}, {0, -3}, {-1, 0}, {2, -1}, {0, -1}, {-1, 2}, {0, 2}};
    PRINT_A(p2, sizeof(p2) / sizeof(Point));
    auto ch = bf::convex_hull(p2, sizeof(p2) / sizeof(Point));
    PRINT_V(ch);
}