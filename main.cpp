#include <iostream>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    using F = Fraction;

    Matrix<3, 3, F> A{};
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            A.data[i][j] = 3 * i * i + 4 * j / 3;
        }
    }

    A.inverse();

    return 0;
}