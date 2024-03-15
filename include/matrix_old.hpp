#pragma once

#include <cstdlib>
#include <iostream>
#include <cassert>

/// @brief Matrix class
/// @tparam T Matrix data type
template <typename T>
class Matrix;

/// @brief Right side product of scalar and matrix
/// @param s Scalar value
/// @param m Matrix
/// @return Result of product
template <typename T>
Matrix<T> operator*(const T &s, const Matrix<T> &m);

/// @brief Calculates matrix determinant by Laplace method
/// @tparam T matrix data type
/// @param m Matrix
/// @return Matrix's determinant
template <typename T>
T lapLaceDeterminant(const Matrix<T> &m);

template <typename T>
class Matrix
{
public:
    /// @brief Empty constructor
    Matrix();

    /// @brief Constructor with matrix order and initial value
    /// @param r Number of rows
    /// @param c Number of columns
    /// @param v Optional initial value for each cell
    Matrix(const size_t &r, const size_t &c, const T &v = T{0});

    /// @brief Constructor with matrix order and data
    /// @param r Number of rows
    /// @param c Number of columns
    /// @param data Matrix data
    Matrix(const size_t &r, const size_t &c, T **data);

    /// @brief Copy constructor
    /// @param m Matrix to be copied
    Matrix(const Matrix<T> &m);

    /// @brief Destructor
    ~Matrix();

    /// @brief Transpose of this matrix
    /// @return This matrix transposed
    Matrix<T> transpose();

    /// @brief Calculate this matrix's determinant
    /// @return The calculated determinant
    T determinant();

    /// @brief Tries to calculate inverse of this matrix. If determinant = 0, throws and error
    /// @return The inverse of this matrix
    Matrix<T> inverse();

    /// @brief Number of rows
    size_t rows;

    /// @brief Number of columns
    size_t cols;

    /// @brief Data pointer
    T **data = nullptr;

    /// @brief Copy assign operator
    /// @param m Matrix to be copied
    /// @return Copied matrix
    Matrix<T> &operator=(const Matrix<T> &m);

    /// @brief Equal check operator
    /// @param m Other matrix
    /// @return Whether 2 matrices have the same data
    bool operator==(const Matrix<T> &m) const;

    /// @brief Addition of 2 matrices
    /// @param m Other matrix
    /// @return Result of addition
    Matrix<T> operator+(const Matrix<T> &m) const;

    /// @brief Addition of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of addition
    Matrix<T> &operator+=(const Matrix<T> &m);

    /// @brief Difference of 2 matrices
    /// @param m Other matrix
    /// @return Result of subtraction
    Matrix<T> operator-(const Matrix<T> &m) const;

    /// @brief Difference of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of subtraction
    Matrix<T> &operator-=(const Matrix<T> &m);

    /// @brief Negative matrix operator
    /// @return This matrix, with all cell's signs flipped
    Matrix<T> operator-() const;

    /// @brief Product of 2 matrices
    /// @param m Other matrix
    /// @return Result of product
    Matrix<T> operator*(const Matrix<T> &m) const;

    /// @brief Product of 2 matrices, then assign
    /// @param m Other matrix
    /// @return Result of product
    Matrix<T> &operator*=(const Matrix<T> &m);

    /// @brief Product of scalar and matrix
    /// @param s Scalar value
    /// @return Result of product
    Matrix<T> operator*(const T &s) const;

    /// @brief Product of scalar and matrix, then assign
    /// @param s Scalar value
    /// @return Result of product
    Matrix<T> &operator*=(const T &s);

    /// @brief Division of matrix by scalar
    /// @param s Scalar value
    /// @return Result of division
    Matrix<T> operator/(const T &s) const;

    /// @brief Division of matrix by scalar, then assign
    /// @param s Scalar value
    /// @return Result of division
    Matrix<T> &operator/=(const T &s);

    /// @brief Identity matrix
    /// @param o Matrix order
    /// @return Identity matrix with given order
    static Matrix<T> identity(const size_t &o);

private:
    /// @brief Allocates memory for matrix data
    /// @param r Number of rows
    /// @param c Number of columns
    /// @param v Optional initial cell value
    void alloc(const size_t &r, const size_t &c, const T &v = T{0});

    /// @brief Frees memory of matrix data
    void free();
};

template <typename T>
void Matrix<T>::alloc(const size_t &r, const size_t &c, const T &v)
{
    if (data != nullptr)
    {
        free();
    }

    // Assign variables
    rows = r;
    cols = c;

    // Alloc and assign cell values
    data = new T *[rows];
    for (size_t i = 0; i < rows; ++i)
    {
        data[i] = new T[cols];
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] = v;
        }
    }
}

template <typename T>
void Matrix<T>::free()
{
    if (data != nullptr)
    {
        for (size_t i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }
}

template <typename T>
Matrix<T>::Matrix()
    : rows{0},
      cols{0}
{
}

template <typename T>
Matrix<T>::Matrix(const size_t &r, const size_t &c, const T &v)
    : rows{r},
      cols{c}
{
    alloc(r, c, v);
}

template <typename T>
Matrix<T>::Matrix(const size_t &r, const size_t &c, T **data)
{
    alloc(r, c);

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            Matrix<T>::data[i][j] = data[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &m)
{
    alloc(m.rows, m.cols, T{0});

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

template <typename T>
Matrix<T>::~Matrix()
{
    free();
}

template <class T>
Matrix<T> Matrix<T>::identity(const size_t &o)
{
    Matrix<T> m{o, o, T{0}};
    for (size_t i = 0; i < o; ++i)
    {
        m.data[i][i] = T{1};
    }

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix m{cols, rows};

    for (size_t j = 0; j < cols; ++j)
    {
        for (size_t i = 0; i < rows; ++i)
        {
            m.data[j][i] = data[i][j];
        }
    }
}

template <typename T>
T lapLaceDeterminant(const Matrix<T> &m)
{
    assert((m.rows == m.cols) && "Determinant is defined only for square matrices");

    // No data
    if (m.rows == 0)
    {
        return 0;
    }

    // Only one cell, determinant is itself
    if (m.rows == 1)
    {
        return m.data[0][0];
    }

    // 2x2, calculate by hand
    if (m.rows == 2)
    {
        return m.data[0][0] * m.data[1][1] - m.data[0][1] * m.data[1][0];
    }

    // From 3x3 up, use Laplace method
    T det = T{0};
    for (size_t i = 0; i < m.rows; ++i)
    {
        if (m.data[0][i] == 0)
            continue;

        // Construct new matrix
        Matrix<T> n{m.rows - 1, m.rows - 1};
        for (size_t j = 0; j < n.rows; ++j)
        {
            for (size_t k = 0; k < n.rows; ++k)
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
T Matrix<T>::determinant()
{
    // LapLace method seems easier to implement, but could be slower
    return lapLaceDeterminant(*this);
}

template <typename T>
Matrix<T> Matrix<T>::inverse()
{
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m)
{
    // No data, exit early
    if (m.data == nullptr)
        return os;

    for (size_t i = 0; i < m.rows; ++i)
    {
        os << "[";
        for (size_t j = 0; j < m.cols; ++j)
        {
            os << m.data[i][j];
            if (j != m.cols - 1)
            {
                os << " ";
            }
        }
        os << "]";
        if (i != m.rows - 1)
        {
            os << "\n";
        }
    }

    return os;
}

template <typename T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &m)
{
    assert((rows == m.rows && cols == m.cols) && "Can only copy matrix of same order");

    if (data == nullptr)
    {
        alloc(rows, cols, T{0});
    }

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> &m) const
{
    if (rows != m.rows || cols != m.cols)
        return false;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            if (data[i][j] != m.data[i][j])
                return false;
        }
    }

    return true;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m) const
{
    Matrix<T> tmp{*this};
    tmp += m;
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &m)
{
    assert((rows == m.rows && cols == m.cols) && "Matrix sum must be between same order matrices");

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] += m.data[i][j];
        }
    }

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &m) const
{
    Matrix<T> tmp{*this};
    tmp -= m;
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &m)
{
    return *this += -m;
}

template <typename T>
Matrix<T> Matrix<T>::operator-() const
{
    Matrix m{*this};

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            m.data[i][j] = -data[i][j];
        }
    }

    return m;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m) const
{
    assert((cols == m.rows) && "Left matrix's cols must be the same as right matrix's rows in matrix-matrix product.");

    Matrix res{rows, m.cols};
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < m.cols; ++j)
        {
            for (size_t k = 0; k < cols; ++k)
                res.data[i][j] += data[i][k] * m.data[k][j];
        }
    }

    return res;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &m)
{
    assert((cols == m.cols && rows == m.rows) && "Matrix product and assign is only defined for matrices of same order");

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < m.cols; ++j)
        {
            for (size_t k = 0; k < cols; ++k)
                data[i][j] += data[i][k] * m.data[k][j];
        }
    }

    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const T &s) const
{
    Matrix<T> tmp{*this};
    tmp *= s;
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator*=(const T &s)
{
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            data[i][j] *= s;
        }
    }

    return *this;
}

template <typename T>
Matrix<T> operator*(const T &s, const Matrix<T> &m)
{
    return m * s;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T &s) const
{
    Matrix tmp{*this};
    tmp /= s;
    return tmp;
}

template <typename T>
Matrix<T> &Matrix<T>::operator/=(const T &s)
{
    return *this *= T{1} / s;
}