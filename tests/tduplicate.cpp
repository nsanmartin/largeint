#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{2};
    int times = 99999;
    
    lint::nat nat {number};
    mpz_t mpz;
    mpz_init_set_ui (mpz, number);


    int i{};
    for (; i < times; i++) {
        nat += nat;
        mpz_add(mpz, mpz, mpz);
        if (!eq_nat_mpz(nat, mpz)) {
            std::cerr << "error suming numbers"<< std::endl
                      << number << "^" << i << std::endl

                      << "nat: " << std::endl << nat << std::endl
                      << "mpz: " << std::endl
                      << mpz_get_str (NULL, 16, mpz)
                      << std::endl;
            exit(1);
        }
    }
    std::cout << "Ok."  << number << "^" << i << std::endl
              << nat.to_string().substr(0, 65) << "..."
              << std::endl; 

}
