#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>
#include <chrono>

void test_random_natural_times_digit () {

    unsigned long multiplo{rand_long(rand_gen)};
    std::string number_str{random_string(rand_size(rand_gen))};

    mpz_class mpz_n{"0x" + number_str};
    mpz_class mpz_m{multiplo};
    mpz_n *= mpz_m;


    lint::natural n { number_str };
    lint::digit_t m {multiplo};
    n *= m;

    std::cout << "Natural with " <<  number_str.size()
              << " digits times " << multiplo << "..."
              << std::flush;
    
    if ( std::string{mpz_n.get_str(16)} == n.to_string() ) {
        std::cout << " Ok.\n";
    } else {
        std::cout << "error." << std::endl;
        std::cerr << "error multiplicating digits" << std::endl;
        exit(1);
    }

}

int main() {
    int number_of_tests {30};
    std::cout << "Comparing results of " << number_of_tests
              << " random tests with gmplib\n"
              << std::flush;
    
    for (int i = 0; i < number_of_tests; ++i) {
        test_random_natural_times_digit ();
    }
}
