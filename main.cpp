#include <iostream>
#include <random>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    srand(time(NULL));

    // Create random 4x4 matrix
    using F = Fraction;
    Matrix<4, 4, F> A{};
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
        {
            A.data[i][j] = rand() % 10 - 5;
        }
    }

    // Show results
    auto inv = A.inverse();
    auto det = A.determinant();
    std::cout << "det(A) = " << det << "\n\n";
    std::cout << "A:\n"
              << A << "\n\n";
    std::cout << "inv(A):\n"
              << inv << "\n";

    // Calculate determinant for a big matrix
    const size_t o = 10;
    Matrix<o, o, F> B{};
    for (size_t i = 0; i < o; ++i)
    {
        for (size_t j = 0; j < o; ++j)
        {
            B.data[i][j] = rand() % 10 - 5;
        }
    }

    auto invB = B.inverse();
    std::cout << "\n==============================";
    std::cout << "\nB:\n"
              << B << "\n\n";
    std::cout << "det(B) = " << B.determinant() << "\n";

    return 0;
}