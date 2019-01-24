#ifndef __LINT_NAT_H
#define __LINT_NAT_H


#include <vector>
#include <iostream>
#include <climits>
#include <cstdint>
#include <limits>
#include <functional>

namespace lint {
    using digit_t = uint64_t;
    using highdigit_t = uint32_t;
    using lowdigit_t = uint32_t;

    
    constexpr int BITS_IN_DIGIT = CHAR_BIT * sizeof(digit_t);
    constexpr int digit_t_len = sizeof(digit_t);
    constexpr digit_t digit_max = std::numeric_limits<digit_t>::max();

    const  digit_t DIGIT_LOW_MASK = 0xffffffff;
    
    class natural {
        std::vector<digit_t> digits;
        void construct_from_hex_string(std::string hexs);
        bool is_max_digit(int i) { return digits.at(i) == digit_t_len; }
        digit_t sum_overflow (digit_t x, digit_t y) {
            return bool{x + y < x};
        }
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
        void transform(std::function<digit_t(digit_t)> f) ;
        void digit_rshift(size_t n) {
            if (n > 0) {
                digits.insert(digits.begin(), n, 0);
            }
        }
        natural(size_t shift, digit_t d)
            : digits{std::vector<digit_t>(shift, 0)} {
            digits.push_back(d);
        }
        natural& add_shifted(const std::vector<digit_t> &ds, size_t fst = 0);

    public:
        void
        mul_digit_pair(digit_t x, digit_t y,
                                digit_t &high, digit_t &low);

        natural() : digits{std::vector<digit_t>(1, 0)} {}
        natural(digit_t n) : digits{std::vector<digit_t>(1, n)} {}
        natural(std::vector<digit_t>& uv) : digits{uv} {
            if (digits.size() == 0) digits.push_back(0);
        }
        natural(std::vector<digit_t> &&uv) : digits{uv}  {
            if (digits.size() == 0) digits.push_back(0);
        }
        natural(std::string);
        natural& operator++();
        bool operator==(const natural &m);
        bool operator<(const natural &m);

        inline bool is_zero() const {
            return digits.size() == 1 && digits[0] == 0;
        }
        
        natural& operator+=(const natural &m);
        natural& operator*=(const natural& m);
        

        friend std::ostream& operator<<(std::ostream& stream, const natural &n);
        std::string to_string();
    };

    natural operator+(natural n, const natural &m);
}


#endif // __LINT_NAT_H
