#include "tests.hpp"

int main(int argc, char ** argv) {
    input_number n{rand_size(rand_gen)};
    input_number m{rand_size(rand_gen)};

    lint::nat sum_nat {n.nat + m.nat};
    mpz_t sum_mpz;
    mpz_init (sum_mpz);
    mpz_add (sum_mpz, n.mpz, m.mpz);
    std::string sum_mpz_str{mpz_get_str (NULL, 16, sum_mpz)};
    if (sum_mpz_str == sum_nat.to_string()) {
        std::cout << "Ok." << std::endl;

    } else {
        std::cout << "error in sum of nat." << std::endl
                  << "input n: "<< std::endl << n.s << std::endl
                  << "input m: "<< std::endl << m.s << std::endl
                  << "mpz res:" << std::endl
                  << sum_mpz_str << std::endl
                  << "nat res:" << std::endl
                  << sum_nat.to_string() << std::endl;
        exit(1);
    }

}
