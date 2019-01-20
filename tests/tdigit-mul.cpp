#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>

int main(int argc, char ** argv)
{
    unsigned long multiplo{0xffffffffffff};
    std::string number_str{"ffffffffffffffffffffffffffffffffffff"};

    // mpz number
    mpz_class mpz_n{"0x" + number_str};
    mpz_class mpz_m{multiplo};

    
    std::cout << "mpz_n: \t" << mpz_n.get_str(16)
              << " times " << mpz_m.get_str(16)
              << std::endl;

    mpz_n *= mpz_m;

    std::cout << "mpz_n *= mpz_m:\n"
              << mpz_n.get_str(16) << std::endl << std::endl;


    // lint number
    lint::natural n { number_str };
    lint::digit_t m {multiplo};
    
    std::cout << "lint n:\t" << n << " times " << multiplo << std::endl;
    n *= m;

    std::cout << "lint n * m:\n"   << n << std::endl;

    // if ( n == k ) {
    //     std::cout << "Ok." << std::endl;
    // } else {
    //     std::cerr << "error multiplicating digits" << std::endl;
    //     exit(1);
    // }
}
