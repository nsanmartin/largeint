#include <iostream>
#include <natural.hpp>
#include <string>

int main(int argc, char ** argv)
{
  
    if (argc != 3) {
        std::cout << "Usage: add-times NUMBER TIMES" << std::endl;
        return 0;
    }

    lint::natural n{std::string{argv[1]}};
    int times{std::stoi(argv[2])};
    
    lint::natural sum;
    for (int i = 0 ; i < times; i++) {
        sum += n;
    }

    std::cout << sum << std::endl;
}
