#include <iostream>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    auto m = Matrix<Fraction>(3, 3);
    m.data[0][0] = {1};
    m.data[0][1] = {-7};
    m.data[0][2] = {4};
    m.data[1][0] = {3, 7};
    m.data[1][1] = {2};
    m.data[1][2] = {1, 2};
    m.data[2][0] = {-5};
    m.data[2][1] = {4,3};
    m.data[2][2] = {2,5};
    std::cout << m.determinant() << "\n";
    std::cout << m.determinant().eval() << "\n";

    return 0;
}