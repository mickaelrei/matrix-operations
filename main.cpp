#include <iostream>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    auto i = Matrix<3, 3, Fraction>::identity();
    std::cout << i << "\n";

    return 0;
}
