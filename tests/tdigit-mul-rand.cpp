#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>

int main(int argc, char ** argv)
{
    unsigned long multiplo{rand_long(rand_gen)};
    std::string number_str{random_string(rand_size(rand_gen))};

    // std::cout << multiplo << std::endl;
    // return 0;
    // mpz number
    mpz_class mpz_n{"0x" + number_str};
    mpz_class mpz_m{multiplo};
    mpz_n *= mpz_m;


    // lint number
    lint::natural n { number_str };
    lint::digit_t m {multiplo};
    n *= m;

    if ( std::string{mpz_n.get_str(16)} == n.to_string() ) {
        std::cout << "Ok." << std::endl;
    } else {
        std::cerr << "error multiplicating digits" << std::endl;
        exit(1);
    }
}
