#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>


void test_natural_div_digit(std::string n_str, std::string m_str, std::string result) {

    lint::natural n { n_str};
    lint::natural m { m_str};
    
    std::cout << n << " div " << m << std::flush;
    n /= m;

    std::cout << " ==\n"   << n << "\n";

    if ( result == n.to_string() ) {
        std::cout << " Ok." << std::endl;
    } else {
        std::cerr << " error dividing digits. expected:\n"
                  << result
                  << std::endl;
        
        exit(1);
    }
}

int main () {

        test_natural_div_digit(
            "fffffffffffffffffffff238f900dd09efffffffffffffffffffffff000012772aaab",
            "f43923a",
            "10c583de95feb0f696c98e316b2b9bdf7206f7d27780c39e95797807896f95d"
        );




}
