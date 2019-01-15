#ifndef __LINT_NAT_H
#define __LINT_NAT_H


#include <vector>
#include <iostream>
#include <climits>
#include <cstdint>

namespace lint {
    using digit_t = uint64_t;
    using highdigit_t = uint32_t;
    using lowdigit_t = uint32_t;

    
    constexpr int BITS_IN_DIGIT = CHAR_BIT * sizeof(digit_t);
    constexpr int digit_t_len = sizeof(digit_t);

    const  digit_t DIGIT_LOW_MASK = 0xffffffff;
    
    class nat {
        std::vector<digit_t> digits;
        void construct_from_hex_string(std::string hexs);
        bool is_max_digit(int i) { digits.at(i) == digit_t_len; }
        inline digit_t nth_bit(digit_t word, int n) {
            return  1 & ((word) >> (n));
        }
        void duplicate();
        inline digit_t low_word(digit_t d) {
            return d & DIGIT_LOW_MASK;
        }
        inline digit_t high_word(digit_t d) {
            return (d >> (BITS_IN_DIGIT / 2));
        }
        void mul_digits_by_high(highdigit_t n);
        void add_digits(const digit_t x, const digit_t y,
                        digit_t &carry, digit_t &sum);
        void mul_digits(digit_t const x, digit_t const y,
                        digit_t &left, digit_t &right);
    public:
        void mul_digits_by_low(lowdigit_t n);

        nat() : digits{std::vector<digit_t>(1, 0)} {}
        nat(digit_t n) : digits{std::vector<digit_t>(1, n)} {}
        nat(std::vector<digit_t> uv) : digits{uv} {
            if (digits.size() == 0) digits.push_back(0);
        }
        nat(std::string);
        nat& operator++();
        bool operator==(const nat &m);
        bool operator<(const nat &m);
        
        nat& operator+=(const nat &m);
        nat& operator*=(const nat &m);
        friend std::ostream& operator<<(std::ostream& stream, const nat &n);
        std::string to_string();
    };

    nat operator+(nat n, const nat &m);
}


#endif // __LINT_NAT_H
