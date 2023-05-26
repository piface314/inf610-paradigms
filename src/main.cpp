#include <iostream>
#include "brute-force.hpp"
#include "exhaustive-search.hpp"
#include "backtracking.hpp"


int main(int argc, char const *argv[]) {
    bf::test();
    std::cout << "\n";
    xs::test();
    std::cout << "\n";
    bt::test();
    return 0;
}
