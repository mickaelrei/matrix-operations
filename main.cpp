#include <iostream>

#include <include/fraction.hpp>
#include <include/matrix.hpp>

int main(int argc, char **argv)
{
    Matrix<2, 15, Fraction> m;
    std::cout << "Matrix <" << m.rows() << "x" << m.cols() << ">\n";
    std::cout << "Matrix of type \"" << typeid(m.data).name() << "\"\n";

    return 0;
}
