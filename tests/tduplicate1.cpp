#include <tests.hpp>

int main(int argc, char ** argv)
{
    unsigned long number{(unsigned long)-1};

    lint::natural natural0 {number};
    lint::natural natural {number};

    natural += natural;
    if (natural < natural0) {
        std::cerr << "error in natural::operand +=(const natural &)"
                  << std::endl;
        exit (1);
    }
    std::cout << "Ok" << std::endl;
}
