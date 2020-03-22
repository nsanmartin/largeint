#include <natural.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <utility>

namespace lint {
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
	size_t nchars{digit_t_len * 2};
	size_t i{};

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
	size_t i{0};
	while (++digits.at(i) == 0 && ++i < digits.size()) 
	    ;
	if (i == digits.size()) {
	    digits.push_back(1);
	}
	return *this;
    }

    void natural::duplicate() {
	digit_t lastbit{0};
	for (size_t i = 0; i < digits.size(); i++) {
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
	for (size_t i = 0; i < digits.size(); i++) {
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
	if (this == &m || digits == m.digits) { duplicate(); return *this; }
	size_t n {m.digits.size()};
	if (n > digits.size()) {
	    digits.insert(digits.end(), n - digits.size(), 0);
	}
    
	int carry{};
	for (size_t i = 0; i < n; i++) {
	    if (carry > 0 && ++digits[i] != 0) { carry = 0;}
	    digits[i] += m.digits[i];
	    carry = digits[i] < m.digits[i] ? 1 : 0;
	}

	if (carry) {
	    if (n < digits.size()) {
		for (size_t i = n; i < digits.size() && ++digits[i] == 0; i++) 
		    ;
	    } else {
		for (size_t i = n; ++digits[i] != 0; i++) {
		    if (i == n) {
			digits.push_back(1);
			break;
		    }
		}
	    }
	}
	return *this;
    }


    
    void
    natural::mul_digit_pair(digit_t x, digit_t y, digit_t &high, digit_t &low) {
	if (x == 0 || y == 0) { high = low = 0; return; }
	low = x * y;
	if (x == low / y) { high = 0; return; }
	digit_t x_low{low_word(x)};
	digit_t x_high{high_word(x)};
	digit_t y_low{low_word(y)};
	digit_t y_high{high_word(y)};

	digit_t ll{x_low * y_low};
	digit_t hl{x_high * y_low};
	digit_t lh{x_low * y_high};
	digit_t hh{x_high * y_high};

	digit_t middle_sum{hl + lh};
	hh += bool {(middle_sum << (BITS_IN_DIGIT / 2)) + ll < ll};
	high = hh + (middle_sum >> (BITS_IN_DIGIT / 2)) + ((digit_t)bool{middle_sum < hl} << (BITS_IN_DIGIT / 2));
    }

    natural& natural::operator*=(const natural &n) {
	if (is_zero()) { return *this; }
	if (n.is_zero()) { digits = std::vector<digit_t> {0}; return *this;}

	std::vector<digit_t> sum(digits.size() + n.digits.size() + 1, 0);
	for (size_t i = 0; i < digits.size(); i++) {
	    digit_t carry{};
	    for (size_t j = 0; j < n.digits.size(); j++) {
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


    digit_t natural::get_d_to_normalize(digit_t v_n_minus_1_minus_2) {
	digit_t v_n_minus_1 {high_word(v_n_minus_1_minus_2) + 1};
	return shift_halfword(1) / v_n_minus_1;
    }

    void natural::normalize_for_div(digit_t& d) {
    	natural high{*this};
    	(*this) *= natural{d};
    	high *= natural{shift_halfword(d)};
    	*this += high;
    }

    size_t natural::halfword_size() const {
	size_t res {digits.size() * 2};
	if (has_zero_on_left()) {
	    --res;
	}
	return res;
    }

    digit_t natural::halfdigit_at(size_t i) const {
	auto n = digits.at(i/2);
	return i % 2 == 0 ?
	    low_word(n) :
	    high_word(n);
    }

    std::pair<digit_t,digit_t> natural:: get_q_hat(natural& div, size_t n, size_t j) {

	digit_t u{shift_halfword(halfdigit_at(n + j)) + halfdigit_at(n + j - 1)};
	digit_t q_hat = u / div.halfdigit_at(n-1);
	digit_t r_hat = u % div.halfdigit_at(n-1);
	return std::make_pair(q_hat, r_hat);
    }

    
    natural& natural::operator/=(const natural &num) {
	if (num.is_zero()) { throw std::runtime_error("zero division"); }
	if (is_zero()) { return *this; }
	if ((*this) < num) { digits = std::vector<digit_t> {0}; return *this;}
    
	digit_t d {get_d_to_normalize(num.back())};
	natural div {num};

	div.normalize_for_div(d);
	normalize_for_div(d);
	//todo: +-1 ?
	size_t n { div.halfword_size() };
	size_t m {halfword_size() - (n - 1)};

	for (size_t j = m; 0 <= j; --j) { 

	    auto qr {get_q_hat(div, n, j)};
	
	    while (qr.first > halfdigit_radix() ||
		   qr.first * div.halfdigit_at(n-2)
		   > shift_halfword(qr.second) + halfdigit_at(j+n-2) ) {
		--qr.first;
		qr.second += div.halfdigit_at(n-1);

		if (qr.second >= halfdigit_radix()) { break; }
	    }
	}
    
	return *this;
    }



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

