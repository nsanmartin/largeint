#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{2};
    int times = 99999;
    
    lint::natural natural {number};
    mpz_t mpz;
    mpz_init_set_ui (mpz, number);


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
    std::cout << "Ok."  << number << "^" << i << std::endl
              << natural.to_string().substr(0, 65) << "..."
              << std::endl; 

}
