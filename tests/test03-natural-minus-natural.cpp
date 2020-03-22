#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>


void test_natural_times_natural(std::string n_str, std::string m_str, std::string result) {

    lint::natural n { n_str};
    lint::natural m { m_str};
    
    std::cout << n << " minus " << m << std::flush;
    n -= m;

    std::cout << " == "   << n;

    if ( result == n.to_string() ) {
        std::cout << " Ok." << std::endl;
    } else {
        std::cerr << " error substracting digits" << std::endl;
        exit(1);
    }
}

int main () {
        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "0",
            "ffffffffffffffffffffffffffffffffffffffffffff"
        );

        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "1",
            "fffffffffffffffffffffffffffffffffffffffffffe"
        );

        
        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "2",
            "fffffffffffffffffffffffffffffffffffffffffffd"
        );

        test_natural_times_natural(
        "ffffffffffffffffffffffffffffffffffffffffffff",
        "ffffffffffffffffffffffffffffffffffffffffffff",
        "0"
        );

        test_natural_times_natural(
        "ffffffffffffffffffffffffffffffffffffffffffff",
        "fffffffffffff00aaaffffffffffffffffffffffff",
        "ff0000000000000ff555000000000000000000000000"
        );

    test_natural_times_natural(
        "ffffff23421afffffff00aaaffffffffffffffffffffffff",
        "ffffff110dfffffffffffffffffffffffffffffffff",
        "ffffef234229ef1ffff00aab000000000000000000000000"
        );


}
