#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>
#include <limits>
#include <random>
#include <gmp.h>


constexpr unsigned max_num_of_digits = 1024 * 1024;

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();

std::random_device r;
std::mt19937 rand_gen(r());
std::uniform_int_distribution<unsigned char> hex_digit(0,15);
std::uniform_int_distribution<unsigned> rand_size(1, max_num_of_digits);
std::uniform_int_distribution<unsigned long> rand_long(0, ulong_max);

char digit_table[] {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f'
        };

std::string random_string (int size) {
    std::string res(size, 0);
    for (auto &c : res) {
        c = digit_table[hex_digit(rand_gen)];
    }
    return res;
}


bool eq_nat_mpz (lint::nat nat, mpz_t mpz) {
    std::string mpz_str{mpz_get_str (NULL, 16, mpz)};
    return mpz_str == nat.to_string();

}
struct input_number {
    unsigned size;
    std::string s;
    lint::nat nat;
    mpz_t mpz;
    input_number(unsigned sz) :
        size{sz}, s{random_string(size)}, nat{s} {
            mpz_init_set_str (mpz, s.c_str(), 16);

            if (mpz_string() != nat.to_string()) {
                std::cerr << "error parsing string" << std::endl;
                exit(1);
            }
        }
    std::string mpz_string() {
        return std::string{mpz_get_str (NULL, 16, mpz)};
    }
};


lint::digit_t nth_bit(lint::digit_t word, int n) {
    return  1 & ((word) >> (n));
}
