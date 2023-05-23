#include <iostream>
#include "brute-force.hpp"

#define PRINT_A(A,N) for(size_t i=0;i<N;++i)std::cout<<(i?",":"")<<A[i];std::cout<<std::endl


void test_bf();

int main(int argc, char const *argv[]) {
    test_bf();
    return 0;
}

void test_bf() {
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
    std::cout << p1[cp.first] << " ~ " << p1[cp.second] << ": " << p1[cp.first].distance(p1[cp.second]) << "\n";
    std::cout << "\n";

    std::cout << "Convex Hull\n";
    Point p2[] = {{0, 0}, {-1, -2}, {1, 0}, {-2, 1}, {0, 1}, {0, -3}, {-1, 0}, {2, -1}, {0, -1}, {-1, 2}, {0, 2}};
    PRINT_A(p2, sizeof(p2) / sizeof(Point));
    auto ch = bf::convex_hull(p2, sizeof(p2) / sizeof(Point));
    PRINT_A(ch.first, ch.second);
}