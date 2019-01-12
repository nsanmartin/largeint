#include <vector>
#include <iostream>

namespace lnum {

    constexpr int ul_len = sizeof(unsigned long);
    
    class nat {
        std::vector<unsigned long> digits;

    public:
        nat() : digits{std::vector<unsigned long>(1, 0)} {}
        nat(unsigned n) : digits{std::vector<unsigned long>(1, n)} {}
        nat(std::vector<unsigned long> uv) : digits{uv} {
            if (digits.size() == 0) digits.push_back(0);
        }

        nat& operator++();

        friend std::ostream& operator<<(std::ostream& stream, const nat &n);
    };
}
