#pragma once

#include <cstdlib>
#include <iostream>

template <size_t R, size_t C, typename T>
class Matrix
{
public:
    Matrix();
    Matrix(T data[R][C]);
    ~Matrix();

    T data[R][C];

    /// @brief Number of rows of this template type
    constexpr size_t rows() const
    {
        return R;
    }

    /// @brief Number of cols of this template type
    constexpr size_t cols() const
    {
        return C;
    }

    static Matrix<R, C, T> identity();
};

/// @brief Prints matrix
/// @tparam T matrix data type
/// @tparam R number of rows
/// @tparam C number of columns
/// @param os ostream
/// @param m matrix to be printed
template <size_t R, size_t C, typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<R, C, T> &m);

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix()
    : data{T{0}} {}

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix(T data[R][C])
    : data{data} {}

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::~Matrix()
{
}

template <size_t R, size_t C, class T>
Matrix<R, C, T> Matrix<R, C, T>::identity()
{
    Matrix<R, C, T> m{};
    for (size_t i = 0; i < R; ++i) {
        for (size_t j = 0; j < C; ++j) {
            if (i == j) {
                m.data[i][j] = T{1};
            } else {
                m.data[i][j] = T{0};
            }
        }
    }

    return m;
}

template <size_t R, size_t C, typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<R, C, T> &m)
{
    for (size_t i = 0; i < R; ++i) {
        os << "[";
        for (size_t j = 0; j < C; ++j) {
            os << m.data[i][j];
            if (j != C - 1) {
                os << " ";
            }
        }
        os << "]\n";
    }

    return os;
}