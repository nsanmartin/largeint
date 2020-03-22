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
            "0",
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "0"
        );

        test_natural_div_digit(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "1",
            "ffffffffffffffffffffffffffffffffffffffffffff"
        );

        
        test_natural_div_digit(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "2",
            "7fffffffffffffffffffffffffffffffffffffffffff"
            );


                test_natural_div_digit(
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
            "2",
            "7ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
            );

        test_natural_div_digit(
            "fffffffffffffffffffff238f900dd09efffffffffffffffffffffff000012772aaab",
            "2",
            "7ffffffffffffffffffff91c7c806e84f7ffffffffffffffffffffff8000093b95555"
        );

                
        test_natural_div_digit(
            "fffffffffffffffffffff238f900dd09efffffffffffffffffffffff000012772aaab",
            "a",
            "199999999999999999999838e5b3494dcb333333333333333333333319999b7251111"
        );

        test_natural_div_digit(
            "fffffffffffffffffffff238f900dd09efffffffffffffffffffffff000012772aaab",
            "f43923a",
            "10c583de95feb0f696c98e316b2b9bdf7206f7d27780c39e95797807896f95d"
        );




}
