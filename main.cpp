#include <iostream>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    using F = Fraction;

    // Questão 1 da lista de Algebra Linear

    Matrix<2, 2, F> A({
        {
            {F{1, 2}, F{1, 3}},
            {F{-2}, F{1, 4}}
        }
    });
    Matrix<2, 2, F> B({
        {
            {F{2, 5}, F{3, 4}},
            {F{-7}, F{-3}}
        }
    });
    Matrix<2, 2, F> C({
        {
            {F{-2, 3}, F{1, 3}},
            {F{-3, 4}, F{-4}}
        }
    });
    Matrix<2, 2, F> D({
        {
            {F{2}, F{-3}},
            {F{-2}, F{-1, 2}}
        }
    });
    Matrix<2, 2, F> E({
        {
            {F{1, 2}, F{-1, 2}},
            {F{-2}, F{0}}
        }
    });

    Matrix<2, 2, F> res = F{2} * A * B - C * D.transpose() - F{5} * E * Matrix<2, 2, F>::identity();

    std::cout << "2AB - C(D.transpose) - 5EI:\n" << res << "\n\n";
    std::cout << "Determinant: " << res.determinant() << "\n";

    return 0;
}