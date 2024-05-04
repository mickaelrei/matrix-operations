#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>
#include <array>

/// @brief Matrix class
/// @tparam T Matrix data type
template <size_t R, size_t C, typename T>
class Matrix;

template <size_t R, size_t C, typename T>
using array2d = std::array<std::array<T, C>, R>;

/// @brief Right side product of scalar and matrix
/// @param s Scalar value
/// @param m Matrix
/// @return Result of product
template <size_t R, size_t C, typename T>
Matrix<R, C, T> operator*(const T &s, const Matrix<R, C, T> &m);

/// @brief Matrix-matrix multiplication
/// @tparam R Left matrix's rows, also resulting matrix's row
/// @tparam M Left matrix's cols and right matrix's rows
/// @tparam C Right matrix's cols, also resulting matrix's cols
/// @tparam T matrix data type
/// @param m0 Left matrix
/// @param m1 Right matrix
/// @return Result of matrix product
template <size_t R, size_t M, size_t C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, M, T> &m0, const Matrix<M, C, T> &m1);

/// @brief Calculates matrix determinant by Laplace method
/// @tparam T matrix data type
/// @param m Matrix
/// @return Matrix's determinant
template <size_t R, size_t C, typename T>
T lapLaceDeterminant(const Matrix<R, C, T> &m);

template <size_t R, size_t C, typename T>
class Matrix
{
public:
    /// @brief Constructor with initial cell value
    /// @param v Optional initial value
    Matrix(const T &v = T{0});

    /// @brief Constructor with matrix data
    /// @param r Number of R
    /// @param c Number of columns
    /// @param data Matrix data
    // Matrix(T data[R][C]);

    /// @brief Constructor from brace initializer list
    Matrix(const array2d<R, C, T> &data);

    /// @brief Copy constructor
    /// @param m Matrix to be copied
    Matrix(const Matrix<R, C, T> &m);

    /// @brief Destructor
    ~Matrix();

    /// @brief Transpose of this matrix
    /// @return This matrix transposed
    Matrix<C, R, T> transpose();

    /// @brief Calculate this matrix's determinant
    /// @return The calculated determinant
    T determinant();

    /// @brief Tries to calculate inverse of this matrix. If determinant = 0, throws and error
    /// @return The inverse of this matrix
    Matrix<R, C, T> inverse();

    /// @brief Data pointer
    T data[R][C] = {T{0}};

    /// @brief Copy assign operator
    /// @param m Matrix to be copied
    /// @return Copied matrix
    Matrix<R, C, T> &operator=(const Matrix<R, C, T> &m);

    /// @brief Equal check operator
    /// @param m Other matrix
    /// @return Whether 2 matrices have the same data
    bool operator==(const Matrix<R, C, T> &m) const;

    /// @brief Addition of 2 matrices
    /// @param m Other matrix
    /// @return Result of addition
    Matrix<R, C, T> operator+(const Matrix<R, C, T> &m) const;

    /// @brief Addition of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of addition
    Matrix<R, C, T> &operator+=(const Matrix<R, C, T> &m);

    /// @brief Difference of 2 matrices
    /// @param m Other matrix
    /// @return Result of subtraction
    Matrix<R, C, T> operator-(const Matrix<R, C, T> &m) const;

    /// @brief Difference of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of subtraction
    Matrix<R, C, T> &operator-=(const Matrix<R, C, T> &m);

    /// @brief Negative matrix operator
    /// @return This matrix, with all cell's signs flipped
    Matrix<R, C, T> operator-() const;

    /// @brief Product of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of product
    Matrix<R, C, T> &operator*=(const Matrix<R, C, T> &m);

    /// @brief Product of scalar and matrix
    /// @param s Scalar value
    /// @return Result of product
    Matrix<R, C, T> operator*(const T &s) const;

    /// @brief Product of scalar and matrix, then assign
    /// @param s Scalar value
    /// @return Result of product
    Matrix<R, C, T> &operator*=(const T &s);

    /// @brief Division of matrix by scalar
    /// @param s Scalar value
    /// @return Result of division
    Matrix<R, C, T> operator/(const T &s) const;

    /// @brief Division of matrix by scalar, then assign
    /// @param s Scalar value
    /// @return Result of division
    Matrix<R, C, T> &operator/=(const T &s);

    /// @brief Identity matrix
    /// @return Identity matrix with given order
    static Matrix<R, C, T> identity();

    /// @brief Elementary operation - swap two rows
    /// @param r0 first row
    /// @param r1 second row
    void swapRows(const size_t &r0, const size_t &r1);

    /// @brief Elementary operation - multiply row by scalar
    /// @param r row to be multiplied
    /// @param s scalar value
    void multiplyRow(const size_t &r, const T &s);

    /// @brief Elementary operation - add on row another row multiplied by scalar
    /// @param r0 row to be added
    /// @param r1 row which will be multiplied and added on top of r0
    /// @param s scalar value
    void addScaledRow(const size_t &r0, const size_t &r1, const T &s = T{1});

private:
    /// @brief Allocates memory for matrix data
    /// @param r Number of R
    /// @param c Number of columns
    /// @param v Optional initial cell value
    void alloc(const size_t &r, const size_t &c, const T &v = T{0});

    /// @brief Frees memory of matrix data
    void free();
};

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix(const T &v)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            data[i][j] = v;
        }
    }
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix(const array2d<R, C, T> &data)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            Matrix<R, C, T>::data[i][j] = data[i][j];
        }
    }
}

// template <size_t R, size_t C, typename T>
// Matrix<R, C, T>::Matrix(T data[R][C])
// {
//     for (size_t i = 0; i < R; ++i)
//     {
//         for (size_t j = 0; j < C; ++j)
//         {
//             Matrix<R, C, T>::data[i][j] = data[i][j];
//         }
//     }
// }

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix(const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::~Matrix()
{
}

template <size_t R, size_t C, class T>
Matrix<R, C, T> Matrix<R, C, T>::identity()
{
    static_assert(R == C, "Identity matrix is only defined for square orders");

    Matrix<R, C, T> m{T{0}};
    for (size_t i = 0; i < R; ++i)
    {
        m.data[i][i] = T{1};
    }

    return m;
}

template <size_t R, size_t C, typename T>
Matrix<C, R, T> Matrix<R, C, T>::transpose()
{
    Matrix<C, R, T> m{};

    for (size_t j = 0; j < C; ++j)
    {
        for (size_t i = 0; i < R; ++i)
        {
            m.data[j][i] = data[i][j];
        }
    }

    return m;
}

template <size_t R, size_t C, typename T>
T lapLaceDeterminant(const Matrix<R, C, T> &m)
{
    static_assert((R == C) && "Determinant is defined only for square matrices");
    std::cout << "laplace for order " << R << "\n";

    // No data
    if (R == 0)
    {
        return 0;
    }

    // Only one cell, determinant is itself
    if (R == 1)
    {
        return m.data[0][0];
    }

    // 2x2, calculate by hand
    if (R == 2)
    {
        return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
    }

    // From 3x3 up, use Laplace method
    T det = T{0};
    for (size_t i = 0; i < R; ++i)
    {
        if (m.data[0][i] == 0)
            continue;

        // Construct new matrix
        Matrix<R - 1, R - 1, T> n{};
        for (size_t j = 0; j < R - 1; ++j)
        {
            for (size_t k = 0; k < R - 1; ++k)
            {
                size_t col = k < i ? k : k + 1;
                n.data[j][k] = m.data[j + 1][col];
            }
        }

        det += T{i & 1 ? -1 : 1} * m.data[0][i] * lapLaceDeterminant(n);
    }

    return det;
}

template <typename T>
T lapLaceDeterminant(const Matrix<1, 1, T> &m)
{
    return m.data[0][0];
}

template <typename T>
T lapLaceDeterminant(const Matrix<2, 2, T> &m)
{
    return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
}

template <size_t R, size_t C, typename T>
T Matrix<R, C, T>::determinant()
{
    // LapLace method seems easier to implement, but could be slower
    return lapLaceDeterminant(*this);
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::inverse()
{
    // IDK
}

template <size_t R, size_t C, typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i)
    {
        os << "[";
        for (size_t j = 0; j < C; ++j)
        {
            os << m.data[i][j];
            if (j != C - 1)
            {
                os << " ";
            }
        }
        os << "]";
        if (i != R - 1)
        {
            os << "\n";
        }
    }

    return os;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator=(const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

template <size_t R, size_t C, typename T>
bool Matrix<R, C, T>::operator==(const Matrix<R, C, T> &m) const
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            if (data[i][j] != m.data[i][j])
                return false;
        }
    }

    return true;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::operator+(const Matrix<R, C, T> &m) const
{
    Matrix<R, C, T> tmp{*this};
    tmp += m;
    return tmp;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator+=(const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            data[i][j] += m.data[i][j];
        }
    }

    return *this;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::operator-(const Matrix<R, C, T> &m) const
{
    Matrix<R, C, T> tmp{*this};
    tmp -= m;
    return tmp;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator-=(const Matrix<R, C, T> &m)
{
    return *this += -m;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::operator-() const
{
    Matrix<R, C, T> m{*this};

    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            m.data[i][j] = -data[i][j];
        }
    }

    return m;
}

template <size_t R, size_t M, size_t C, typename T>
Matrix<R, C, T> operator*(const Matrix<R, M, T> &m0, const Matrix<M, C, T> &m1)
{
    Matrix<R, C, T> res{};
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            for (size_t k = 0; k < M; ++k)
                res.data[i][j] += m0.data[i][k] * m1.data[k][j];
        }
    }

    return res;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator*=(const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            for (size_t k = 0; k < C; ++k)
                data[i][j] += data[i][k] * m.data[k][j];
        }
    }

    return *this;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::operator*(const T &s) const
{
    Matrix<R, C, T> tmp{*this};
    tmp *= s;
    return tmp;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator*=(const T &s)
{
    for (size_t i = 0; i < R; ++i)
    {
        for (size_t j = 0; j < C; ++j)
        {
            data[i][j] *= s;
        }
    }

    return *this;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> operator*(const T &s, const Matrix<R, C, T> &m)
{
    return m * s;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> Matrix<R, C, T>::operator/(const T &s) const
{
    Matrix tmp{*this};
    tmp /= s;
    return tmp;
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T> &Matrix<R, C, T>::operator/=(const T &s)
{
    return *this *= T{1} / s;
}

template <size_t R, size_t C, typename T>
void Matrix<R, C, T>::swapRows(const size_t &r0, const size_t &r1)
{
    for (size_t i = 0; i < C; ++i)
    {
        T tmp{data[r0][i]};
        data[r0][i] = data[r1][i];
        data[r1][i] = tmp;
    }
}

template <size_t R, size_t C, typename T>
void Matrix<R, C, T>::multiplyRow(const size_t &r, const T &s)
{
    for (size_t i = 0; i < C; ++i)
    {
        data[r][i] *= s;
    }
}

template <size_t R, size_t C, typename T>
void Matrix<R, C, T>::addScaledRow(const size_t &r0, const size_t &r1, const T &s)
{
    for (size_t i = 0; i < C; ++i)
    {
        data[r0][i] += s * data[r1][i];
    }
}