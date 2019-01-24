#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>
#include <chrono>


    
void mmm(int sz) {
    std::cout << sz << " ";
    std::string n_str{random_string(sz)};
    std::string m_str{random_string(sz)};

    // mpz number
    mpz_class mpz_n{"0x" + n_str};
    mpz_class mpz_m{"0x" + m_str};

    auto start_mpz = std::chrono::steady_clock::now();
    mpz_n += mpz_m;
    auto end_mpz = std::chrono::steady_clock::now();
    auto diff_mpz = end_mpz - start_mpz;
    std::cout << std::chrono::duration <double, std::milli> (diff_mpz).count()
         << " ";


    // lint number
    lint::natural n { n_str};
    lint::natural m { m_str};

    auto start_lint = std::chrono::steady_clock::now();
    n += m;
    auto end_lint = std::chrono::steady_clock::now();
    auto diff_lint = end_lint - start_lint;

    std::cout << std::chrono::duration <double, std::milli> (diff_lint).count()
              << std::endl;


    bool exit_fail {false};
    if ( std::string{mpz_n.get_str(16)} != n.to_string() ) {
        std::cerr << "error in natural::mul" << std::endl;
        exit_fail = true;
    }
    if (exit_fail) { exit(1); }
}


unsigned min = 1000;
unsigned max = 6000000;
unsigned step = 100;

int main(int argc, char ** argv) {
    for (unsigned i = min; i < max; i+= step) {
        mmm(i);
    }
}
