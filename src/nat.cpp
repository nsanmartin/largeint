#include <nat.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>

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

nat& nat::operator+=(const nat &m) {
    int difflen { m.digits.size() - digits.size()};
    if (difflen > 0) {
        digits.insert(digits.end(), difflen, 0);
    }
    int carry{};
    for (int i = 0; i < m.digits.size(); i++) {
        if (carry > 0 && ++digits[i] != 0) { carry = 0;}
        carry = digits[i] + m.digits[i] < digits[i];
        digits[i] += m.digits[i];
    }
    
    for (int i = m.digits.size(); i < digits.size(); i++) {
        if (carry > 0 && ++digits[i] != 0) { carry = 0;}
    }

    if (carry) { digits.push_back(1); }
    return *this;
}



nat& nat::operator+=(const std::vector<bool> &c) {
    
    int difflen { digits.size() - c.size()};
    if (difflen > 0) {
        digits.insert(digits.end(), difflen, 0);
    }
    std::vector<bool> carrys(c.size() + 1, 0);
    for (int i = 0; i < c.size(); i++) {
        digits[i] += c[i] ? 1 : 0;
        carrys[i + 1] = digits[i]  == 0;
    }

    while (carrys.size() > 0 && carrys.back() == false) { carrys.pop_back(); }
    if (carrys.size() > 0)
        *this += carrys;
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

