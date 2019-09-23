#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>
#include <chrono>

int main(int argc, char ** argv)
{

    std::string n_str{random_string(rand_size(rand_gen))};
    std::string m_str{random_string(rand_size(rand_gen))};

    std::cout << "Multiplying 2 naturals with " << n_str.size() << " and " << m_str.size()
              << " digits respectively... " << std::flush;
    // mpz number
    mpz_class mpz_n{"0x" + n_str};
    mpz_class mpz_m{"0x" + m_str};

    mpz_n *= mpz_m;

    // lint number
    lint::natural n { n_str};
    lint::natural m { m_str};

    n *= m;

    if ( std::string{mpz_n.get_str(16)} != n.to_string() ) {
        std::cerr << "error multiplicating digits" << std::endl;
        std::cerr << std::string{mpz_n.get_str(16)} << std::endl;
        std::cerr << n << std::endl;
        exit(1);
    } else {
        std::cout << "Ok.\n";
    }
}
