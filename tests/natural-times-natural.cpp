#include <tests.hpp>
#include <gmpxx.h>
#include <iomanip>


void test_natural_times_natural(std::string n_str, std::string m_str, std::string result) {

    lint::natural n { n_str};
    lint::natural m { m_str};
    
    std::cout << n << " times " << m << std::flush;
    n *= m;

    std::cout << " == "   << n;

    if ( result == n.to_string() ) {
        std::cout << " Ok." << std::endl;
    } else {
        std::cerr << "error multiplicating digits" << std::endl;
        exit(1);
    }
}

int main () {
        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "0",
            "0"
        );

        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "1",
            "ffffffffffffffffffffffffffffffffffffffffffff"
        );

        
        test_natural_times_natural(
            "ffffffffffffffffffffffffffffffffffffffffffff",
            "2",
            "1fffffffffffffffffffffffffffffffffffffffffffe"
        );

    test_natural_times_natural(
        "ffffffffffffffffffffffffffffffffffffffffffff",
        "fffffffffffff00aaaffffffffffffffffffffffff",
        "fffffffffffff00aaafffffffffffffffffffffffeff0000000000000ff555000000000000000000000001"
        );

    test_natural_times_natural(
        "ffffff110dfffffffffffffffffffffffffffffffff",
        "ffffff23421afffffff00aaaffffffffffffffffffffffff",
        "fffffe34501bce09365884ab0ee52af059ffffffffefffff0dcbdf3ef20000ff555000000000000000000000001"
        );


}
