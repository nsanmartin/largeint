#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{(unsigned long)-1};

    std::vector<lint::digit_t> ds {
        0xfffffffff, 0xfffffffff, 0xfffffffff, 0xfffffffff
            };
    
    lint::natural n { ds};
    lint::lowdigit_t m {2};
    lint::natural k{n};
    //std::cout << "n: " << n << "\t m: " << m << std::endl;
    n.mul_digits_by_low(m);
    k += k;
    // std::cout << "n * m: "   << n << std::endl
    //           << "n + n: " << k << std::endl;
    if ( n == k ) {
        std::cout << "Ok." << std::endl;
    } else {
        std::cerr << "error multiplicating digits" << std::endl;
        exit(1);
    }
}
