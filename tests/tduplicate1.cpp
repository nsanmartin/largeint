#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{(unsigned long)-1};

    lint::nat nat0 {number};
    lint::nat nat {number};

    nat += nat;
    if (nat < nat0) {
        std::cerr << "error in nat::operand +=(const nat &)"
                  << std::endl;
        exit (1);
    }
    std::cout << "Ok" << std::endl;
}
