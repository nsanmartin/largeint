#include <iostream>
#include <nat.hpp>

int main(int argc, char ** argv)
{
  
    if (argc != 3) {
        std::cout << "Usage: add NUMBER NUMBER" << std::endl;
        return 0;
    }

    std::string fst{argv[1]};
    std::string snd{argv[2]};

    lnum::nat sum {lnum::nat{fst} + lnum::nat{snd}};

    std::cout << sum << std::endl;
}
