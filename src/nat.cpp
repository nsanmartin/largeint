#include <nat.hpp>
#include <iostream>
#include <iomanip>

using namespace lnum;

nat& nat::operator++() {
    int i{0};
    while (++digits.at(i) == 0 && ++i < digits.size()) 
        ;
    if (i == digits.size()) {
        digits.push_back(1);
    }
    return *this;
}

namespace lnum {
    std::ostream& operator<<(std::ostream& stream, const nat &n) {
        size_t i{n.digits.size() - 1};
        stream << std::hex << n.digits[i];
        for (; 0 != i;) {
            i--;
            stream << std::setfill('0') << std::setw(ul_len * 2) << std::hex
                   << n.digits.at(i);
        }
        return stream;
    }
}

