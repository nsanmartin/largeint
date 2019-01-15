#include <nat.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>

using namespace lint;
nat::nat(std::string s) {
    std::string hex_prefix{"0x"};
    // bool is_hex{std::mismatch(s.begin(), s.end(), hex_prefix.begin()) == hex_prefix.end()};
    // if (is_hex) {
    //     s.erase(s.begin(), s.begin() + 2);
        construct_from_hex_string(s);
        //int most_significative_digits {s.size() % (ul_len * 2)}; 
        
//}
    
}

void nat::construct_from_hex_string(std::string hexs) {
    int nchars{digit_t_len * 2};
    int i{};

    std::size_t find {hexs.find_first_not_of('0')};
    if (find != std::string::npos) { hexs.erase(0, find); }

    for (; hexs.size() - i >= nchars; i += nchars) {
        std::string digit_str{
            hexs.end() - i - nchars, hexs.end() - i
                };
        
        digit_t digit_ul;
        std::stringstream{digit_str} >> std::hex >> digit_ul;
        digits.push_back(digit_ul);

    }

    if (i < hexs.size()) {
        std::string digit_str{
            hexs.begin(), hexs.end() - i};
        digit_t digit_ul;
        std::stringstream{digit_str} >> std::hex >> digit_ul;
        digits.push_back(digit_ul);
    }
}


nat& nat::operator++() {
    int i{0};
    while (++digits.at(i) == 0 && ++i < digits.size()) 
        ;
    if (i == digits.size()) {
        digits.push_back(1);
    }
    return *this;
}

void nat::duplicate() {
    digit_t lastbit{0};
    for (int i = 0; i < digits.size(); i++) {
        digit_t tmp {nth_bit(digits[i], BITS_IN_DIGIT - 1)};
        digits[i] <<= 1;
        digits[i] |= lastbit;
        lastbit = tmp;
    }
    if (lastbit == 1) {
        digits.push_back(1);
        
    }
}

bool nat::operator==(const nat &m) {
    if (digits.size() != m.digits.size()) { return false; }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != m.digits[i]) { return false; }
    }
    return true;
}

bool nat::operator<(const nat &m) {
    if (digits.size() != m.digits.size()) {
        return digits.size() < m.digits.size();
    }
    for (int i = digits.size(); i >= 0; i--) {
        if (digits[i] == m.digits[i]) { continue; }
        return digits[i] < m.digits[i];
    }
    return false;
}

nat& nat::operator+=(const nat &m) {
    if (this == &m) {
        duplicate();
        return *this;
    }
    
    if (m.digits.size() > digits.size()) {
        digits.insert(digits.end(), m.digits.size() - digits.size(), 0);
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

void nat::mul_digits_by_low(lowdigit_t n) {
    digit_t carry{};
    for (auto& d : digits) {
        
        digit_t low{low_word(d) * static_cast<digit_t>(n)};
        digit_t high{high_word(d) * static_cast<digit_t>(n)};
        // overflow in carry + low??
        d = (carry + low) | (high << (BITS_IN_DIGIT / 2));
        carry = high >> (BITS_IN_DIGIT / 2);
    }
    if (carry != 0) {
        digits.push_back(carry);
    }
}

void nat::mul_digits_by_high(highdigit_t n) {
    digit_t carry{};

    digit_t fst_high{high_word(digits[0]) * static_cast<digit_t>(n)};
    // todo!!!
    
    for (auto& d : digits) {
        
        digit_t low{low_word(d) * static_cast<digit_t>(n)};
        digit_t high{high_word(d) * static_cast<digit_t>(n)};

        d = (carry + low) | (high << (BITS_IN_DIGIT / 2));
        carry = high >> (BITS_IN_DIGIT / 2);
    }
    if (carry != 0) {
        digits.push_back(carry);
    }
}


nat& nat::operator*=(const nat &m) {
    // for (int i = 0; i < digits.size(); i++) {
    //     digit_t mlow{ low_word(m.digits[i]) };
    //     for (int j = i; j < digits.size(); j++) {
    //         digit_t low{ low_word(digits[j]) };
            
    //         digit_t prodlow {mlow * low};
    //         digit_t prodhigh {mlow * hight};
    //     }
        
    // }
    return *this;
}
void nat::add_digits (const digit_t x, const digit_t y,
                      digit_t &carry, digit_t &sum)
{
    carry = x + y < x ? 1 : 0;
    sum = x + y;
}


void nat::mul_digits(digit_t const x, digit_t const y,
                digit_t &left, digit_t &right) {
    if (x == 0 || y == 0) { left = right = 0; return; }

    digit_t sum, carry;
    left = 0;
    right = 1 & y ? x : 0;
    digit_t n = 1;

    while (y >> n && n < BITS_IN_DIGIT) {

        add_digits(right, nth_bit(y, n) ? x << n : 0, carry, sum);
            
        left += nth_bit(y, n) ? x >> (BITS_IN_DIGIT - n)  : 0;
        left += carry;
        right = sum;
        n++;
    }
}


namespace lint {
    std::ostream& operator<<(std::ostream& stream, const nat &n) {
        size_t i{n.digits.size() - 1};
        stream << std::hex << n.digits[i];
        for (; 0 != i;) {
            i--;
            stream << std::setfill('0') << std::setw(digit_t_len * 2) << std::hex
                   << n.digits.at(i);
        }
        return stream;
    }

    
    std::string nat::to_string() {
        std::stringstream out_str; out_str << *this;
        return out_str.str();
        
    }

    nat operator+(nat n, const nat &m) { return n+= m; }
}

