#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>
#include <sstream>

int main(int argc, char ** argv)
{
    lint::digit_t n{random_digit()};
    lint::digit_t m{random_digit()};

    mpz_class mpz_n{n};
    mpz_class mpz_m{m};

    
    mpz_n *= mpz_m;


    lint::natural nat_n {} ;

    lint::digit_t low{};
    lint::digit_t high{};
    
    nat_n.mul_digit_pair(n, m, high, low);

    std::string mpz_string {mpz_n.get_str(16)};
    std::stringstream ss;
    ss << std::hex <<high << std::setfill('0')
       << std::setw(lint::digit_t_len * 2) << low;
    std::string lint_string{ss.str()};

    if ( mpz_string == lint_string ) {
        std::cout << "Ok." << std::endl;
    } else {
        std::cerr << "error multiplicating digits" << std::endl;
        std::cout << "n: " << std::hex << n << std::endl
                  << "m: " << std::hex << m << std::endl
                  << "mpz: \t" << mpz_string << std::endl
                  << "lint:\t" << lint_string << std::endl;
        exit(1);
    }
}
