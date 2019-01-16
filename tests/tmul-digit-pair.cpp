#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>

int main(int argc, char ** argv)
{
    // todo: test with random
    // lint::digit_t n{0xffffffffffffffff};
    // lint::digit_t m{0xffffffffffffffff};

    lint::digit_t n{0x1ffff0000};
    lint::digit_t m{0x1ffff0000};

    mpz_class mpz_n{n};
    mpz_class mpz_m{m};

    
    std::cout << "mpz: \t" << mpz_n.get_str(16)
              << " times " << mpz_m.get_str(16)
              << std::endl;

    mpz_n *= mpz_m;

    std::cout << "mpz_n *= mpz_m:\n"
              << mpz_n.get_str(16)
              << "\t len: " << std::string(mpz_n.get_str(16)).size()
              << std::endl << std::endl;

    lint::natural nat_n {} ;

    lint::digit_t low{};
    lint::digit_t high{};
    
    nat_n.mul_digit_pair(n, m, high, low);
    
    std::cout << std::hex << std::setw(lint::digit_t_len)
              << "lint \t" << n << " times " << m << std::endl
              << "high: "<<  std::setfill('0')
              << std::setw(2*lint::digit_t_len)
              << high << std::endl
              << "low:  "<<  std::setfill('0')
              << std::setw(2*lint::digit_t_len) 
              << low << std::endl;

    std::cout << "\nlint nat_n.mul_digit_pair(n, m, high, low)" << std::endl
              << std::hex <<  std::setfill('0')
              << std::setw(2*lint::digit_t_len)
              << high <<  std::setfill('0')
              << std::setw(2*lint::digit_t_len) 
              << low << std::endl
              <<  std::setfill('0')
              << std::setw(4*lint::digit_t_len) 
              << mpz_n.get_str(16) << std::endl;




    // if ( n == k ) {
    //     std::cout << "Ok." << std::endl;
    // } else {
    //     std::cerr << "error multiplicating digits" << std::endl;
    //     exit(1);
    // }
}
