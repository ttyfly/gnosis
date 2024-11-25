#include "gnosis/gnosis.hpp"

int main() {
    constexpr gnosis::Fix<int64_t, 32> a(2.5f);
    constexpr gnosis::Fix<int64_t, 32> b(4.f);
    std::cout << (a / b) << std::endl;
    std::cout << gnosis::sqrt(a) << std::endl;
    return 0;
}