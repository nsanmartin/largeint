#include <tests.hpp>
#include <iomanip>

void test_mul_digit_pair(lint::digit_t n, lint::digit_t m,
                        lint::digit_t expected_high,
                        lint::digit_t expected_low) {

    lint::digit_t low{};
    lint::digit_t high{};
    lint::natural nat_n{};

    std::cout << std::hex << n << " times " << m;
    nat_n.mul_digit_pair(n, m, high, low);

    
    if ( high == expected_high &&  low == expected_low) {
        std::cout << " Ok.\n";
    } else {
        std::cerr << std::hex << " error!";
        std::cerr << "obtained: (" <<  high << ", " << low << ")\n";
        std::cerr << "expected: (" << expected_high << ", " << expected_low << ")\n";
        std::exit(1);
    }
        
}

int main () {
    test_mul_digit_pair(0x100000000, 0x100000000, 0x1, 0x0);
    test_mul_digit_pair(0x8000000000000000, 0x2, 0x1, 0x0);
    test_mul_digit_pair(0x1ffff0000, 0x1ffff0000, 0x3, 0xfffc000100000000);
    test_mul_digit_pair(0x7aa0fd923232, 0x199adffda09, 0xc43e8e, 0x78bbfa0532b057c2);
    test_mul_digit_pair(0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffffffffffe, 0x1);

}
