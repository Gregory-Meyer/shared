#include "vec_wrapper.h"

#include <cassert>
#include <iostream>

int main([[maybe_unused]] int argc, const char *const argv[]) {
    assert(argc >= 2);

    Vec v(argv[1]);

    v.push_back(15);
    v.push_back(10);
    v.push_back(5);

    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << '\n';
    }
}
