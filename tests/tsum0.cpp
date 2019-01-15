#include <string>
#include <vector>
#include <iostream>
#include <natural.hpp>
#include <limits>

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


int main() {

    lint::natural n{std::vector<unsigned long>{
            ulong_max, ulong_max, ulong_max
                }};
    lint::natural m{std::vector<unsigned long>{1}};
    std::cout << n << std::endl;
    std::cout << m << std::endl;
    n += m;
    std::cout << n  << std::endl;

}
