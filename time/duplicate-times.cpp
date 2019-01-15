#include <iostream>
#include <nat.hpp>
#include <string>

int main(int argc, char ** argv)
{
    if (argc != 3) {
        std::cout << "Usage: add-times NUMBER TIMES" << std::endl;
        return 0;
    }
       
    lint::nat nat{std::string{argv[1]}};
    int times{std::stoi(argv[2])};
       
    std::cout << nat << "  num: " << argv[1]
              << "\t times: 0x" << times
              << std::endl;
    for (int i = 0 ; i < times; i++) {
        nat += nat;
    }
    std::cout << nat << std::endl;
}
