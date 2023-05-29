#include <iostream>
#include "utils.hpp"
#include "brute-force.hpp"
#include "exhaustive-search.hpp"
#include "backtracking.hpp"
#include "divide-conquer.hpp"
#include "dynamic-programming.hpp"


int main(int argc, char const *argv[]) {
    bf::test();
    std::cout << "\n";
    xs::test();
    std::cout << "\n";
    bt::test();
    std::cout << "\n";
    dc::test();
    std::cout << "\n";
    dp::test();
    return 0;
}
