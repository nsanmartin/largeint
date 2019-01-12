#include <vector>
#include <iostream>

namespace lnum {

    class nat {
        std::vector<unsigned> digits;

    public:
        nat() : digits{std::vector<unsigned>(1, 0)} {}
        nat(unsigned n) : digits{std::vector<unsigned>(1, n)} {}
        nat(std::vector<unsigned> uv) : digits{uv} {
            if (digits.size() == 0) digits.push_back(0);
        }

        nat& operator++();

        friend std::ostream& operator<<(std::ostream& stream, const nat &n);
    };
}
