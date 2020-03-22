#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>
#include <chrono>
#include <algorithm>

int main(int argc, char ** argv)
{

    std::string n_str{random_string(rand_size(rand_gen))};
    std::string m_str{random_string(rand_size(rand_gen))};

    if (n_str.size() < m_str.size() ||
        (n_str.size() < m_str.size() &&
         std::lexicographical_compare(n_str.begin(), n_str.end(), m_str.begin(), m_str.end()))) {

        std::swap(n_str, m_str);
    }
    
    std::cout << "Dividing naturals with " << n_str.size() << " and " << m_str.size()
              << " digits..." << std::flush;

    // mpz number
    mpz_class mpz_n{"0x" + n_str};
    mpz_class mpz_m{"0x" + m_str};

    mpz_n /= mpz_m;


    // lint number
    lint::natural n { n_str};
    lint::natural m { m_str};

    n /= m;

    if ( std::string{mpz_n.get_str(16)} == n.to_string() ) {
        std::cout << " Ok." << std::endl;
    } else {
        std::cerr << "\nerror dividing naturals!" << std::endl;
        exit(1);
    }
}
