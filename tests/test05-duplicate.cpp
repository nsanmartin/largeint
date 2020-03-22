#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{2};
    int times = 10000;
    
    lint::natural natural {number};
    mpz_t mpz;
    mpz_init_set_ui (mpz, number);

    std::cout << "Comparing with gmplib results of duplicating number 2 "
              << times << " times (might take some time if many times)" << std::endl;

    int i{};
    for (; i < times; i++) {
        natural += natural;
        mpz_add(mpz, mpz, mpz);
        if (!eq_natural_mpz(natural, mpz)) {
            std::cerr << "error suming numbers"<< std::endl
                      << number << "^" << i << std::endl

                      << "natural: " << std::endl << natural << std::endl
                      << "mpz: " << std::endl
                      << mpz_get_str (NULL, 16, mpz)
                      << std::endl;
            exit(1);
        }
    }
    std::cout << "Ok.\n"; 

}
