#include "dynamic-programming.hpp"

std::pair<int, std::vector<int>> dp::coin_row(int *coins, size_t n) {
    int c[n+1] = {0, coins[0]};
    size_t prev[n+1] = {0, 0};
    for (size_t i = 1; i < n; ++i)
        if (coins[i] + c[i-1] > c[i])
            c[i+1] = coins[i] + c[i-1], prev[i+1] = i - 1;
        else
            c[i+1] = c[i], prev[i+1] = i;

    std::cout << "prev: "; PRINT_A(prev, (n+1));
    std::pair<int, std::vector<int>> out = {c[n], std::vector<int>()};
    size_t i = n;
    do {
        size_t p = prev[i];
        if (i - p > 1 || i == 1)
            out.second.push_back(coins[i - 1]);
        i = p;
    } while (i > 0);
    return out;
}

std::vector<int> dp::change_making(int n, int *coins, size_t m) {
    int c[n+1] = {0}, inf = std::numeric_limits<int>::max();
    size_t prev[n+1] = {0};
    for (int i = 1; i <= n; ++i) {
        int c_min = inf;
        for (size_t k = 0; k < m; ++k)
            if (i >= coins[k] && c[i - coins[k]] < c_min)
                c_min = c[i - coins[k]], prev[i] = i - coins[k];
        c[i] = c_min + 1;
    }
    std::vector<int> out;
    size_t i = n;
    do {
        size_t p = prev[i];
        out.push_back(i - p);
        i = p;
    } while (i > 0);
    return out;
}

std::pair<int, std::vector<std::pair<size_t,size_t>>> dp::coin_collecting(bool *c, size_t m, size_t n) {
    std::vector<std::pair<size_t,size_t>> out;
    int f[m*n] = {c[0]};
    for (size_t i = 1; i < n; ++i)
        f[i] = f[i-1] + c[i];
    for (size_t i = 1; i < m; ++i) {
        f[i*n] = f[(i-1)*n] + c[i*n];
        for (size_t j = 1; j < n; ++j)
            f[i*n + j] = std::max(f[(i-1)*n + j], f[i*n + j-1]) + c[i*n + j];
    }

    size_t i = m-1, j = n-1;
    while (i > 0 || j > 0) {
        out.emplace_back(i, j);
        if (j == 0 || (i > 0 && f[(i-1)*n + j] > f[i*n + j-1]))
            --i;
        else
            --j;
    }
    out.emplace_back(0, 0);
    std::reverse(out.begin(), out.end());
    return std::pair(f[m*n-1], out);
}

std::pair<int, Range> dp::max_subseq_sum(int *a, size_t n) {
    int s[n+1] = {0};
    size_t ri = 0, rj = 0;
    for (size_t i = 1; i <= n; ++i)
        s[i] = std::max(s[i-1] + a[i-1], a[i-1]);
    for (size_t i = 1; i <= n; ++i)
        if (s[i] > s[rj])
            rj = i;
    for (size_t i = rj; i >= 0 && s[i] >= 0; --i)
        ri = i;
    return std::pair(s[rj], Range {ri - 1, rj});
}

std::vector<size_t> dp::knapsack(int *w, double *v, int w_max, size_t n) {
    std::vector<size_t> out;
    return out;
}

bool *dp::transitive_closure(bool *adj, size_t n) {
    bool *tc = new bool[n*n] {0};
    return tc;
}

int *dp::all_pairs_shortest_pairs(int *w, size_t n) {
    int *apsp = new int[n*n] {0};
    return apsp;
}


void dp::test() {
    std::cout << "=== Dynamic Programming ===\n";

    std::cout << "Coin Row Problem\n";
    int coins1[] = {5, 1, 2, 10, 6, 2};
    PRINT_A(coins1, sizeof(coins1) / sizeof(int));
    auto cr = dp::coin_row(coins1, sizeof(coins1) / sizeof(int));
    std::cout << cr.first << ": ";
    PRINT_V(cr.second);
    std::cout << "\n";

    std::cout << "Change Making Problem\n";
    int coins2[] = {1, 3, 4};
    auto cm = dp::change_making(6, coins2, sizeof(coins2) / sizeof(int));
    std::cout << "6 : ";
    PRINT_A(coins2, sizeof(coins2) / sizeof(int));
    PRINT_V(cm);
    std::cout << "\n";

    std::cout << "Coin Collecting\n";
    bool coins3[] = {
        0, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 0, 1, 0, 1,
        0, 0, 1, 0, 0, 1,
        1, 0, 0, 0, 1, 0,
    };
    auto cc = dp::coin_collecting(coins3, 5, 6);
    std::cout << "Coins: " << cc.first << " ";
    PRINT_V(cc.second);
    std::cout << "\n";

    std::cout << "Maximum Subsequence Sum (MSS)\n";
    int a3[] = {4, 2, -7, 3, 0, -2, 1, 5, -2};
    PRINT_A(a3, sizeof(a3) / sizeof(int));
    auto mss = dp::max_subseq_sum(a3, sizeof(a3) / sizeof(int));
    std::cout << mss.first << " @ " << mss.second << "\n";
    int a4[] = {-2, 11, -4, 13, -5, 2};
    PRINT_A(a4, sizeof(a4) / sizeof(int));
    auto mss2 = dp::max_subseq_sum(a4, sizeof(a4) / sizeof(int));
    std::cout << mss2.first << " @ " << mss2.second << "\n";
    std::cout << "\n";

    std::cout << "Knapsack 01\n";
    int w[]    = {2, 1, 2, 1, 3};
    double v[] = {3, 1, 4, 1, 5};
    std::vector<size_t> ks = dp::knapsack(w, v, 5, sizeof(w) / sizeof(int));
    std::vector<std::pair<int,double>> items;
    for (auto it : ks)
        items.emplace_back(w[it], v[it]);
    PRINT_V(items);
    std::cout << "\n";

    std::cout << "Transitive Closure\n";
    bool adj[] = {
        0, 1, 0, 0,
        0, 0, 0, 1,
        0, 0, 0, 0,
        1, 0, 1, 0,
    };
    bool *tc = dp::transitive_closure(adj, 4);
    PRINT_M(tc, 4, 4);
    delete [] tc;
    std::cout << "\n";

    std::cout << "All Pairs Shortest Paths\n";
    int inf = std::numeric_limits<int>::max();
    int weights[] = {
          0, inf,   3, inf,
          2,   0, inf, inf,
        inf,   7,   0,   1,
          6, inf, inf,   0,
    };
    int *apsp = dp::all_pairs_shortest_pairs(weights, 4);
    PRINT_M(apsp, 4, 4);
    delete [] apsp;
}