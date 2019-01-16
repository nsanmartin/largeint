#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>

int main(int argc, char ** argv)
{
    unsigned long number{(unsigned long)-1};
    std::string number_str{"ffffffffffffffffffffffffffffffffffff"};

    mpz_class mpz_n{"0x" + number_str};
    lint::digit_t dos{2};
    lint::digit_t multiplo {dos << (lint::BITS_IN_DIGIT / 2)};
    mpz_class mpz_m{multiplo};

    
    std::cout << "mpz_n: \t" << mpz_n.get_str(16)
              << " times " << mpz_m.get_str(16)
              << std::endl;

    mpz_n *= mpz_m;

    std::cout << "mpz_n *= mpz_m:\n"
              << mpz_n.get_str(16) << std::endl << std::endl;

    lint::natural n { number_str };
    lint::highdigit_t m {2};
    
    std::cout << "lint n:\t" << n << " times " << multiplo << std::endl;
    n.mul_digits_by_high(m);

    std::cout << "lint n * m:\n"   << n << std::endl;

    // if ( n == k ) {
    //     std::cout << "Ok." << std::endl;
    // } else {
    //     std::cerr << "error multiplicating digits" << std::endl;
    //     exit(1);
    // }
}
