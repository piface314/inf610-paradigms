#include "backtracking.hpp"

bool queens_ok(size_t *q, size_t n) {
    for (size_t i = 0; i < n; ++i)
        if (q[i] == q[n] || std::abs((long)n - (long)i) == std::abs((long)q[n] - (long)q[i]))
            return false;
    return true;
}

bool n_queens_r(size_t *q, size_t i, size_t n) {
    if (i == n)
        return true;
    for (size_t k = 0; k < n; ++k) {
        q[i] = k;
        if (queens_ok(q, i) && n_queens_r(q, i+1, n))
            return true;
    }
    return false;
}

std::vector<size_t> bt::n_queens(size_t n) {
    std::vector<size_t> out;
    size_t q[n];
    bool ok = n_queens_r(q, 0, n);
    if (ok)
        for (size_t i = 0; i < n; ++i)
            out.push_back(q[i]);
    return out;
}

void subset_sum_r(std::vector<std::vector<int>> &out,
                  std::vector<int> &stack,
                  int m, int *w, size_t n, int s, int t) {
    if (s == m)
        return out.push_back(stack);
    if (n == 0)
        return;
    if (s + t >= m) {
        subset_sum_r(out, stack, m, w + 1, n - 1, s, t - *w);
        if (s + *w <= m) {
            stack.push_back(*w);
            subset_sum_r(out, stack, m, w + 1, n - 1, s + *w, t - *w);
            stack.pop_back();
        }
    }
}

std::vector<std::vector<int>> bt::subset_sum(int m, int *w, size_t n) {
    std::vector<std::vector<int>> out;
    std::vector<int> stack;
    int w_[n], t = 0; 
    for (size_t i = 0; i < n; ++i)
        w_[i] = w[i], t += w[i];
    std::sort(w_, w_ + n);
    subset_sum_r(out, stack, m, w_, n, 0, t);
    return out;
}

void bt::test() {
    std::cout << "=== Backtracking ===\n";
    std::cout << "N Queens\n";
    std::vector<size_t> q = bt::n_queens(4);
    PRINT_V(q);
    std::cout << "\n";

    std::cout << "Subset Sum\n";
    int m = 31, w[] = {13, 11, 24, 7};
    auto ssets = bt::subset_sum(m, w, sizeof(w)/sizeof(int));
    for (auto subset : ssets)
        PRINT_V(subset);
}