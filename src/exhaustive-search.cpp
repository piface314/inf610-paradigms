#include "exhaustive-search.hpp"

std::vector<size_t> xs::traveling_salesman(double *d, size_t n) {
    std::vector<size_t> out;
    size_t *idx = new size_t[n];
    double best_val = std::numeric_limits<double>::max();

    for (size_t i = 0; i < n; ++i)
        idx[i] = i;

    std::function<void(size_t*,size_t)> f = [&](size_t *ids, size_t n) {
        double w = 0;
        for (size_t i = 1; i < n; ++i)
            w += d[ids[i-1]*n + ids[i]];
        if (w < best_val) {
            best_val = w;
            out.clear();
            for (size_t i = 0; i < n; ++i)
                out.push_back(ids[i]);
        }
    };
    permutations(idx, n, f);
    delete [] idx;
    return out;
}

std::vector<size_t> xs::job_scheduling(double *c, size_t n) {
    std::vector<size_t> out;
    size_t *idx = new size_t[n];
    double best_val = std::numeric_limits<double>::max();
    for (size_t i = 0; i < n; ++i)
        idx[i] = i;

    std::function<void(size_t*,size_t)> f = [&](size_t *ids, size_t n) {
        double w = 0;
        for (size_t i = 0; i < n; ++i)
            w += c[i*n + ids[i]];
        if (w < best_val) {
            best_val = w;
            out.clear();
            for (size_t i = 0; i < n; ++i)
                out.push_back(ids[i]);
        }
    };

    permutations(idx, n, f);
    delete [] idx;
    return out;
}

std::vector<size_t> xs::knapsack(int *w, double *v, int w_max, size_t n) {
    std::vector<size_t> out;
    size_t *idx = new size_t[n];
    double best_val = 0;
    for (size_t i = 0; i < n; ++i)
        idx[i] = i;

    std::function<void(size_t*,size_t)> f = [&](size_t *ids, size_t n) {
        double total_v = 0.0;
        int total_w = 0;
        for (size_t i = 0; i < n; ++i)
            total_v += v[ids[i]], total_w += w[ids[i]];
        if (total_w <= w_max && total_v > best_val) {
            best_val = total_v;
            out.clear();
            for (size_t i = 0; i < n; ++i)
                out.push_back(ids[i]);
        }
    };

    power_set(idx, n, f);
    delete [] idx;

    return out;
}

void xs::test() {   
    std::cout << "=== Exhaustive Search ===\n";
    char sample[] = { 'A', 'B', 'C', 'D' };

    std::function<void(char*,size_t)> f = [](char *v, size_t n) { PRINT_A(v, n); };
    std::cout << "Permutations\n";
    xs::permutations(sample, sizeof(sample) / sizeof(char), f);
    std::cout << "\n";

    std::cout << "Power set\n";
    xs::power_set(sample, sizeof(sample) / sizeof(char), f);
    std::cout << "\n";

    std::cout << "TSP\n";
    double d[] = {
        0, 3, 1, 4,
        3, 0, 1, 5,
        1, 1, 0, 9,
        4, 5, 9, 0,
    };
    std::vector<size_t> tsp = xs::traveling_salesman(d, 4);
    PRINT_V(tsp);
    std::cout << "\n";

    std::cout << "Job Scheduling\n";
    double c[] = {
        3, 1, 4, 1,
        5, 9, 2, 6,
        5, 3, 5, 8,
        9, 7, 9, 3,
    };
    std::vector<size_t> js = xs::job_scheduling(c, 4);
    PRINT_V(js);
    std::cout << "\n";

    std::cout << "Knapsack 01\n";
    int w[]    = {2, 1, 2, 1, 3};
    double v[] = {3, 1, 4, 1, 5};
    std::vector<size_t> ks = xs::knapsack(w, v, 5, sizeof(w) / sizeof(int));
    std::vector<std::pair<int,double>> items;
    for (auto it : ks)
        items.emplace_back(w[it], v[it]);
    PRINT_V(items);
}
