#include <tests.hpp>
#include <iomanip>



void test_natural_times_digit(std::string natural, lint::digit_t digit, std::string resultado) {

    lint::natural n { natural };
    std::cout << n << " *= " << digit << " == "; 
     
    n *= digit;

    std::cout << n << ' ';
    if (resultado == n.to_string()) {
        std::cout << "Ok\n";
    } else {
        std::cerr << "error!";
        std::exit(1);
    }
}

int main() {
    test_natural_times_digit("ffffffffffffffffffffffffffffffffffff", 0x0, "0");
    test_natural_times_digit("ffffffffffffffffffffffffffffffffffff", 0x1, "ffffffffffffffffffffffffffffffffffff");
    test_natural_times_digit("ffffffffffffffffffffffffffffffffffff", 0x2, "1fffffffffffffffffffffffffffffffffffe");
    test_natural_times_digit("ffffffffffffffffffffffffffffffffffff", 0xffffffffffff, "fffffffffffeffffffffffffffffffffffff000000000001");
}


