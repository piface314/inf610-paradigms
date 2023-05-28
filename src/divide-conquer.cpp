#include "divide-conquer.hpp"

size_t dc::binary_search(int k, int *x, size_t n) {
    size_t i = 0, j = n - 1;
    while (i < j) {
        size_t m = i + ((j - i) >> 1);
        if (x[m] < k)
            i = m + 1;
        else if (x[m] > k)
            j = m - 1;
        else
            return m;
    }
    return x[i] == k ? i : n;
}

void quicksort_r(int *x, size_t l, size_t r) {
    if (l + 1 >= r)
        return;
    size_t i = l, j = r - 1;
    int pivot = x[l + ((r - l) >> 1)];
    
    do {
        while (x[i] < pivot) ++i;
        while (x[j] > pivot) --j;
        if (i <= j)
            std::swap(x[i++], x[j--]);
    } while (i <= j);
    
    quicksort_r(x, l, j + 1);
    quicksort_r(x, i, r);
}

void dc::quicksort(int *x, size_t n) {
    quicksort_r(x, 0, n);
}

void mergesort_r(int *x, int *buffer, size_t l, size_t r) {
    if (l + 1 >= r)
        return;
    size_t m = l + ((r - l) >> 1);
    mergesort_r(x, buffer, l, m);
    mergesort_r(x, buffer, m, r);
    size_t i = l, j = m, k = 0;
    while (i < m && j < r)
        buffer[k++] = x[x[i] < x[j] ? i++ : j++];
    while (i < m)
        buffer[k++] = x[i++];
    while (j < r)
        buffer[k++] = x[j++];
    for (k = 0; k < r - l; ++k)
        x[l+k] = buffer[k];
}

void dc::mergesort(int *x, size_t n) {
    int buffer[n];
    mergesort_r(x, buffer, 0, n);
}

void convex_hull_r(std::vector<Point> &out, Line papb, std::vector<Point> p) {
    if (p.empty())
        return;
    auto m = p.begin();
    for (auto it = p.begin() + 1; it != p.end(); ++it)
        if (papb.distance(*it) > papb.distance(*m))
            m = it;
    std::vector<Point> s1, s2;
    Line papm { papb.a, *m }, pmpb { *m, papb.b };
    for (auto it = p.begin(); it != p.end(); ++it)
        if (it == m)
            continue;
        else if (papm.side(*it) > 0)
            s1.push_back(*it);
        else if (pmpb.side(*it) > 0)
            s2.push_back(*it);
    out.push_back(*m);
    convex_hull_r(out, papm, s1);
    convex_hull_r(out, pmpb, s2);
}

std::vector<Point> dc::convex_hull(Point *p, size_t n) {
    std::vector<Point> out;
    if (n <= 2) {
        for (size_t i = 0; i < n; ++i)
            out.push_back(p[i]);
    } else {
        size_t a = 0, b = 0;
        for (size_t i = 1; i < n; ++i)
            if (p[i].x < p[a].x)
                a = i;
            else if (p[i].x > p[b].x)
                b = i;
        std::vector<Point> s1, s2;
        double side;
        Line papb { p[a], p[b] }, pbpa { p[b], p[a] };
        for (size_t i = 0; i < n; ++i)
            if (i == a || i == b)
                continue;
            else if ((side = papb.side(p[i])) > 0)
                s1.push_back(p[i]);
            else if (side < 0)
                s2.push_back(p[i]);
        out.push_back(p[a]);
        out.push_back(p[b]);
        convex_hull_r(out, papb, s1);
        convex_hull_r(out, pbpa, s2);
    }
    return out;
}

std::pair<Point, Point> closest_pair_r(Point *p, Point *q, size_t *idx, Range r) {
    size_t n = r.j - r.i;
    if (n < 3)
        return std::pair(p[r.i], p[r.i+1]);
    if (n == 3) {
        double d01 = p[r.i].distance(p[r.i+1]);
        double d02 = p[r.i].distance(p[r.i+2]);
        double d12 = p[r.i+1].distance(p[r.i+2]);
        return d01 < d02
            ? (d01 < d12 ? std::pair(p[r.i], p[r.i+1]) : std::pair(p[r.i+1], p[r.i+2]))
            : (d02 < d12 ? std::pair(p[r.i], p[r.i+2]) : std::pair(p[r.i+1], p[r.i+2]));
    }
    size_t n2 = n / 2;
    auto pL = closest_pair_r(p, q, idx, {r.i, r.i + n2});
    auto pR = closest_pair_r(p, q, idx, {r.i + n2, r.j});
    double d, dL = pL.first.distance(pL.second), dR = pR.first.distance(pR.second);
    std::pair<Point, Point> cp;
    if (dL < dR)
        cp = pL, d = dL;
    else
        cp = pR, d = dR;
    double m = p[n2].x;
    std::vector<Point> s;
    for (size_t i = r.i; i < r.j; ++i)
        if (std::abs(q[idx[i]].x - m) < d)
            s.push_back(q[idx[i]]);
    double dmin = d;
    for (size_t i = 0; i + 1 < s.size(); ++i)
        for (size_t k = i + 1; k < s.size() && std::abs(s[i].y - s[k].y) < dmin; ++k)
            if ((d = s[i].distance(s[k])) < dmin)
                cp = std::pair(s[i], s[k]), dmin = d;
    return cp;
}

std::pair<Point, Point> dc::closest_pair(Point *p, size_t n) {
    Point p_[n], q[n];
    for (size_t i = 0; i < n; ++i)
        q[i] = { p[i].y, p[i].x };
    std::sort(q, q + n);
    std::pair<Point,size_t> idx[n];
    size_t idx_[n];
    for (size_t i = 0; i < n; ++i) {
        q[i] = { q[i].y, q[i].x };
        idx[i] = std::pair(q[i], i);
    }
    std::sort(idx, idx + n);
    for (size_t i = 0; i < n; ++i)
        p_[i] = idx[i].first, idx_[i] = idx[i].second;
    return closest_pair_r(p_, q, idx_, {0, n});
}

std::pair<int, Range> dc::max_subseq_sum(int *a, size_t n) {
    std::pair<int, Range> out;
    return out;   
}

void dc::test() {
    std::cout << "=== Divide and Conquer ===\n";

    std::cout << "Binary Search\n";
    int x1[] = { -42, -7, -6, 0, 2, 3, 5, 7, 11 };
    PRINT_A(x1, sizeof(x1) / sizeof(int));
    std::cout << "6? " << dc::binary_search(6, x1, sizeof(x1) / sizeof(int)) << "\n";
    std::cout << "11? " << dc::binary_search(11, x1, sizeof(x1) / sizeof(int)) << "\n";
    std::cout << "0? " << dc::binary_search(0, x1, sizeof(x1) / sizeof(int)) << "\n";
    std::cout << "30? " << dc::binary_search(30, x1, sizeof(x1) / sizeof(int)) << "\n";
    std::cout << "-42? " << dc::binary_search(-42, x1, sizeof(x1) / sizeof(int)) << "\n";
    std::cout << "\n";

    std::cout << "Quicksort\n";
    int x2[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 };
    PRINT_A(x2, sizeof(x2) / sizeof(int));
    dc::quicksort(x2, sizeof(x2) / sizeof(int));
    PRINT_A(x2, sizeof(x2) / sizeof(int));
    std::cout << "\n";

    std::cout << "Mergesort\n";
    int x3[] = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2, 3, 8, 4, 6 };
    PRINT_A(x3, sizeof(x3) / sizeof(int));
    dc::mergesort(x3, sizeof(x3) / sizeof(int));
    PRINT_A(x3, sizeof(x3) / sizeof(int));
    std::cout << "\n";

    std::cout << "Convex Hull\n";
    Point p2[] = {{0, 0}, {-1, -2}, {1, 0}, {-2, 1}, {0, 1}, {0, -3}, {-1, 0}, {2, -1}, {0, -1}, {-1, 2}, {0, 2}};
    PRINT_A(p2, sizeof(p2) / sizeof(Point));
    auto ch = dc::convex_hull(p2, sizeof(p2) / sizeof(Point));
    PRINT_V(ch);
    std::cout << "\n";

    std::cout << "Closest Pair\n";
    Point p1[] = {{1, 2}, {0, -4}, {3, 2}, {-2, 3}, {-1, -1}, {-3, 0}, {-2, -2}, {0, -1}, {2, -2}};
    // Point p1[] = {{-2,-2}, {-2,3}, {-3,0}};
    PRINT_A(p1, sizeof(p1) / sizeof(Point));
    auto cp = dc::closest_pair(p1, sizeof(p1) / sizeof(Point));
    std::cout << cp.first << " ~ " << cp.second << ": " << cp.first.distance(cp.second) << "\n";
    std::cout << "\n";

    std::cout << "Maximum Subsequence Sum (MSS)\n";
    int a3[] = {4, 2, -7, 3, 0, -2, 1, 5, -2};
    PRINT_A(a3, sizeof(a3) / sizeof(int));
    auto mss = dc::max_subseq_sum(a3, sizeof(a3) / sizeof(int));
    std::cout << mss.first << " @ " << mss.second << "\n";
    int a4[] = {-2, 11, -4, 13, -5, 2};
    PRINT_A(a4, sizeof(a4) / sizeof(int));
    auto mss2 = dc::max_subseq_sum(a4, sizeof(a4) / sizeof(int));
    std::cout << mss2.first << " @ " << mss2.second << "\n";
}