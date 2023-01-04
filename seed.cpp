#include <iostream>
#include <random>
#include <cstdlib>

int main()
{
// Seed with a real random value, if available

std::mt19937 m(0);
std::uniform_int_distribution<int> r(0, INT_MAX);

std::cout << r(m) << " " << r(m) << " " << r(m) << std::endl;

return EXIT_SUCCESS;

// GNU: 1178568022 1273124119 1535857466
// MSVC: 924231285 398764591 209652396
// Intel,IntelLLVM: 209652396 398764591 924231285
}
