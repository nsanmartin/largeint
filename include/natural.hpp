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
    using halfdigit_t = uint64_t;

    using highdigit_t = uint32_t;
    using lowdigit_t = uint32_t;

    constexpr int BITS_IN_DIGIT = CHAR_BIT * sizeof(digit_t);
    constexpr int digit_t_len = sizeof(digit_t);
    constexpr digit_t digit_max = std::numeric_limits<digit_t>::max();

    constexpr  digit_t DIGIT_LOW_MASK = 0xffffffff; 
    constexpr  digit_t DIGIT_HIGH_MASK = ~(digit_t)0xffffffff;
   

    inline constexpr digit_t shift_halfword(digit_t n) {
        return n << 32; 
    }

    constexpr digit_t halfdigit_radix() { return shift_halfword(1); }
    
    inline digit_t low_word(digit_t d) {
	return d & DIGIT_LOW_MASK;
    }
    inline digit_t high_word(digit_t d) {
	return (d >> (BITS_IN_DIGIT / 2));
    }

    inline void set_low_word(digit_t& x, halfdigit_t d) {
	x &= DIGIT_HIGH_MASK;
        x |= static_cast<digit_t>(d);
    }
    
    inline void set_high_word(digit_t& x, halfdigit_t d) {
	x &= DIGIT_LOW_MASK;
        x |= shift_halfword(d);
    }

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

        void digit_rshift(size_t n) {
            if (n > 0) { digits.insert(digits.begin(), n, 0); }
        }
        natural(size_t shift, digit_t d)
            : digits{std::vector<digit_t>(shift, 0)} {
            digits.push_back(d);
        }
        natural& add_shifted(const std::vector<digit_t> &ds, size_t fst = 0);

	digit_t get_d_to_normalize(digit_t v_n_minus_1_minus_2);
	std::pair<digit_t,digit_t> get_q_hat(natural& div, size_t n, size_t j);
	
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
	bool has_zero_on_left() const { return back() < halfdigit_radix(); }
        inline bool is_zero() const {
            return digits.size() == 1 && digits[0] == 0;
        }
	digit_t back() const { return digits.back(); }
	digit_t secondlast() const { return *(digits.rbegin() + 1); }
        natural& operator+=(const natural &m);
        natural& operator-=(const natural &m);
        natural& operator*=(const natural& m);
	natural& operator/=(const natural &n);

        void divide_by_halfword(const natural &num);
	halfdigit_t halfdigit_at(size_t i) const;
        void set_halfdigit_at(size_t i, halfdigit_t n);

	// halfdigit_t halfback() const ;
	
	void normalize_for_div(digit_t& n);
	void get_q_hat(natural& div);
	size_t halfword_size() const;
        friend std::ostream& operator<<(std::ostream& stream, const natural &n);
        std::string to_string();
    };

    natural operator+(natural n, const natural &m);
}


#endif // __LINT_NAT_H
