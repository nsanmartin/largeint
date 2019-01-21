#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>

int main(int argc, char ** argv)
{
    std::string m_str{"ffffffffffffffffffffffffffffffffffffffffffff"};
    std::string n_str{"fffffffffffff00aaaffffffffffffffffffffffff"};
    // std::string n_str{random_string(rand_size(rand_gen))};
    // std::string m_str{random_string(rand_size(rand_gen))};

    // mpz number
    mpz_class mpz_n{"0x" + n_str};
    mpz_class mpz_m{"0x" + m_str};

    
    std::cout << "mpz_n: \t" << mpz_n.get_str(16)
              << " times " << mpz_m.get_str(16)
              << std::endl;

    mpz_n *= mpz_m;

    std::cout << "mpz_n *= mpz_m:\n"
              << mpz_n.get_str(16) << std::endl << std::endl;


    // lint number
    lint::natural n { n_str};
    lint::natural m { m_str};
    
    std::cout << "lint n:\t" << n << " times " << m << std::endl;
    n *= m;

    std::cout << "lint n * m:\n"   << n << std::endl;

    if ( std::string{mpz_n.get_str(16)} == n.to_string() ) {
        std::cout << "Ok." << std::endl;
    } else {
        std::cerr << "error multiplicating digits" << std::endl;
        exit(1);
    }
}
