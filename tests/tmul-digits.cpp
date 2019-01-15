#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{(unsigned long)-1};

    std::vector<lint::digit_t> ds {
        0xfffffffff, 0xfffffffff, 0xfffffffff, 0xfffffffff
            };
    
    lint::nat n { ds};
    lint::lowdigit_t m {2};
    lint::nat k{n};
    std::cout << "n: " << n << "\t m: " << m << std::endl;
    n.mul_digits_by_low(m);
    k += k;
    std::cout << "n * m: "   << n << std::endl
              << "n + n: " << k << std::endl;
    // if (nat < nat0) {
    //     std::cerr << "error in nat::operand +=(const nat &)"
    //               << std::endl;
    //     exit (1);
    // }
    
    //std::cout << "Ok" << std::endl;
}
