#include <natural.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <utility>

using namespace lint;

void natural::transform(std::function<digit_t(digit_t)> f)  {
    std::transform(digits.begin(), digits.end(), digits.begin(), f);
}

natural::natural(std::string s) {
    std::string hex_prefix{"0x"};
    // bool is_hex{std::mismatch(s.begin(), s.end(), hex_prefix.begin()) == hex_prefix.end()};
    // if (is_hex) {
    //     s.erase(s.begin(), s.begin() + 2);
        construct_from_hex_string(s);
        //int most_significative_digits {s.size() % (ul_len * 2)}; 
        
//}
    
}

void natural::construct_from_hex_string(std::string hexs) {
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


natural& natural::operator++() {
    int i{0};
    while (++digits.at(i) == 0 && ++i < digits.size()) 
        ;
    if (i == digits.size()) {
        digits.push_back(1);
    }
    return *this;
}

void natural::duplicate() {
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

bool natural::operator==(const natural &m) {
    if (digits.size() != m.digits.size()) { return false; }
    for (int i = 0; i < digits.size(); i++) {
        if (digits[i] != m.digits[i]) { return false; }
    }
    return true;
}

bool natural::operator<(const natural &m) {
    if (digits.size() != m.digits.size()) {
        return digits.size() < m.digits.size();
    }
    for (int i = digits.size(); i >= 0; i--) {
        if (digits[i] == m.digits[i]) { continue; }
        return digits[i] < m.digits[i];
    }
    return false;
}

natural& natural::operator+=(const natural &m) {
    if (this == &m) { duplicate(); return *this; }
    const std::vector<digit_t> &ds{m.digits};
    this->add(ds);
    return *this;
}

natural&
natural::add (const std::vector<digit_t> &vector, size_t fst) {
    if (digits == vector && fst == 0) { duplicate(); return *this; }
    size_t n {vector.size() + fst};
    if (n > digits.size()) {
        digits.insert(digits.end(), n - digits.size(), 0);
    }
    
    int carry{};
    for (int i = fst; i < n; i++) {
        if (carry > 0 && ++digits[i] != 0) { carry = 0;}
        carry = digits[i] + vector[i - fst] < digits[i];
        digits[i] += vector[i - fst];
    }
    
    for (int i = n; i < digits.size(); i++) {
        if (carry > 0 && ++digits[i] != 0) { carry = 0;}
    }

    if (carry) { digits.push_back(1); }
    return *this;
}


natural& natural::operator*=(const digit_t d) {
    if (is_zero()) { return *this; }
    if (d == 0) { digits = std::vector<digit_t> {0}; return *this;}
    digit_t dlow{low_word(d)};
    digit_t dhigh{high_word(d)};
    std::vector<digit_t> dlow_lows, dlow_highs, dhigh_lows, dhigh_highs;
    
    std::transform(digits.begin(), digits.end(),
                   std::back_inserter(dlow_highs),
                   [dlow, this](digit_t x) {
                       return dlow * high_word(x); });

    std::transform(digits.begin(), digits.end(),
                   std::back_inserter(dhigh_lows),
                   [dhigh, this](digit_t x) {
                       return dhigh * low_word(x); });

    std::transform(digits.begin(), digits.end(),
                   std::back_inserter(dhigh_highs),
                   [dhigh, this](digit_t x) {
                       return dhigh * high_word(x); });

    // low times low is already in it's place
    transform([dlow, this](digit_t x) { return dlow * low_word(x); });

    // the 'middle sum' is half digit shifted
    natural low_middle_sum{std::move(dlow_highs)};
    low_middle_sum += dhigh_lows;


    
    // split the middle
    // the 'low middle' must be shifted half digit to the left,
    // then it can safetly be sumed to this.
    
    natural high_middle_sum {low_middle_sum};
    low_middle_sum.transform([] (digit_t x) {
            return x  << (BITS_IN_DIGIT / 2);
        });
    *this += low_middle_sum;

    // the 'high middle' must be shifted half digit to the right.
    high_middle_sum.transform([] (digit_t x) {
            return x  >> (BITS_IN_DIGIT / 2);
        });
    
    // maybe we can optimize this:
    //high_middle_sum.digit_rshift(1);
    
    this->add(high_middle_sum.digits, 1);

    // the 'high high' part must be shifted a digit to the right,
    // this may algo be optimized
    //dhigh_highs.insert(dhigh_highs.begin(), 0);
    this->add(dhigh_highs, 1);

    while (digits.size() > 0 && digits.back() == 0) {
        digits.pop_back();
    }
    return *this;
}


natural& natural::operator*=(const natural& m) {
    if (is_zero()) { return *this; }
    if (m.is_zero()) { digits = std::vector<digit_t> {0}; return *this;}

    natural accumulator{};
    
    for (size_t i = 0; i < m.digits.size(); i++) {
        if (m.digits[i] != 0) {
            natural mds{*this};
            mds *= m.digits[i];
            // todo: optimize?
            // mds.digit_rshift(i);
            // accumulator += mds;
            accumulator.add(mds.digits, i);
        }
    }
    *this = accumulator;
    return *this;
}

void
natural::mul_digit_pair(digit_t x, digit_t y, digit_t &high, digit_t &low) {
    if (x == 0 || y == 0) { high = low = 0; return; }
    digit_t x_low{low_word(x)};
    digit_t x_high{high_word(x)};
    digit_t y_low{low_word(y)};
    digit_t y_high{high_word(y)};

    digit_t ll{x_low * y_low};
    digit_t hl{x_high * y_low};
    digit_t lh{x_low * y_high};
    digit_t hh{x_high * y_high};

    digit_t middle_sum{hl + lh};
    bool carry{middle_sum < hl};

    digit_t low_middle {middle_sum << (BITS_IN_DIGIT / 2)};
    if (ll + low_middle < ll) {
        assert(hh < digit_max);
        hh++;

    }
    low = ll + low_middle;

    high = hh + (middle_sum >> (BITS_IN_DIGIT / 2));
    if (carry) {
        high += ((digit_t)1) << (BITS_IN_DIGIT / 2);
    }

}

natural& natural::mul(const natural &n) {
    if (is_zero()) { return *this; }
    if (n.is_zero()) { digits = std::vector<digit_t> {0}; return *this;}

    std::vector<digit_t> sum(digits.size() + n.digits.size() + 1, 0);
    for (int i = 0; i < digits.size(); i++) {
        digit_t carry{};
        for (int j = 0; j < n.digits.size(); j++) {
            digit_t high, low;
            mul_digit_pair(digits[i], n.digits[j], high, low);
            low += carry;
            if (low < carry) { high++; }
            sum[i + j] += low;
            if (sum[i + j] < low) { high++; }
            carry = high;
        }
        sum[i + n.digits.size()] += carry;
        
    }
    while (sum.size() > 0 && sum.back() == 0) { sum.pop_back(); }
    digits = sum;
    return *this;
}


namespace lint {
    std::ostream& operator<<(std::ostream& stream, const natural &n) {
        size_t i{n.digits.size() - 1};
        stream << std::hex << n.digits[i];
        for (; 0 != i;) {
            i--;
            stream << std::setfill('0') << std::setw(digit_t_len * 2) << std::hex
                   << n.digits.at(i);
        }
        return stream;
    }

    
    std::string natural::to_string() {
        std::stringstream out_str; out_str << *this;
        return out_str.str();
        
    }

    natural operator+(natural n, const natural &m) { return n+= m; }
}

