#pragma once

#include <cstdlib>
#include <iostream>

template <size_t R, size_t C, typename T>
class Matrix
{
public:
    Matrix();
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

// TODO: Search why i can't define these on another file (src/matrix.cpp)
template <size_t R, size_t C, typename T>
Matrix<R, C, T>::Matrix()
{
}

template <size_t R, size_t C, typename T>
Matrix<R, C, T>::~Matrix()
{
}

template <size_t R, size_t C, class T>
Matrix<R, C, T> Matrix<R, C, T>::identity()
{
    return Matrix<R, C, T>{};
}
