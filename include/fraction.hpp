#pragma once

#include <ostream>

class Fraction
{
public:
    /// @brief Fraction numerator
    int numerator;

    /// @brief Fraction denominator
    int denominator;

    /// @brief Empty constructor
    Fraction();

    /// @brief Constructor with only numerator
    Fraction(const int &numerator);

    /// @brief Constructor with both numerator and denominator
    Fraction(const int &numerator, const int &denominator);

    /// @brief Copy constructor
    /// @param f Fraction to be copied
    Fraction(const Fraction &f);

    /// @brief Destructor
    ~Fraction();

    /// @brief Get inverse of fraction (raised to -1)
    /// @return Inverse of fraction
    Fraction inverse();

    /// @brief Evaluate fraction, that is, divide numerator by denominator
    /// @return Result of evaluated fraction
    float eval();

    /// @brief Reduces fraction so that numerator and denominator don't have any common divisor
    void reduce();

    /// @brief Copy assignment constructor
    /// @param f Fraction to be copied
    /// @return Fraction copied
    Fraction &operator=(const Fraction &f);

    /// @brief Equal check operator
    /// @param f Fraction to check
    /// @return Whether 2 fractions are the same
    bool operator==(const Fraction &f) const;

    /// @brief Add fraction
    /// @param f Second fraction
    /// @return Result of addition
    Fraction operator+(const Fraction &f) const;

    /// @brief Add fraction and assign
    /// @param f Second fraction
    /// @return Result of addition
    Fraction &operator+=(const Fraction &f);

    /// @brief Add fraction and integer
    /// @param s Integer value
    /// @return Result of addition
    Fraction operator+(const int &s) const;

    /// @brief Add fraction and integer and assign
    /// @param s Integer value
    /// @return Result of addition
    Fraction &operator+=(const int &s);

    /// @brief Right-side fraction addition with integer
    /// @param s Integer value
    /// @param f Fraction
    /// @return Result of addition
    friend Fraction operator+(const int &s, const Fraction &f);

    /// @brief Subtract fraction
    /// @param f Second Fraction
    /// @return Result of subtraction
    Fraction operator-(const Fraction &f) const;

    /// @brief Subtract fraction and assign
    /// @param f Second Fraction
    /// @return Result of subtraction
    Fraction &operator-=(const Fraction &f);

    /// @brief Add fraction and integer
    /// @param s Second fraction
    /// @return Result of subtraction
    Fraction operator-(const int &s) const;

    /// @brief Add fraction and integer and assign
    /// @param s Second fraction
    /// @return Result of subtraction
    Fraction &operator-=(const int &s);

    /// @brief Right-side fraction subtraction with integer
    /// @param s Integer value
    /// @param f Fraction
    /// @return Result of subtraction
    friend Fraction operator-(const int &s, const Fraction &f);

    Fraction operator-() const;

    /// @brief Multiply fraction
    /// @param f Second Fraction
    /// @return Result of multiplication
    Fraction operator*(const Fraction &f) const;

    /// @brief Multiply fraction and assign
    /// @param f Second Fraction
    /// @return Result of multiplication
    Fraction &operator*=(const Fraction &f);

    /// @brief Multiply fraction by integer
    /// @param s Scale value
    /// @return Result of multiplication
    Fraction operator*(const int &s) const;

    /// @brief Multiply fraction by integer and assign
    /// @param s Scale value
    /// @return Result of multiplication
    Fraction &operator*=(const int &s);

    /// @brief Right-side fraction multiplication by integer
    /// @param s Integer value
    /// @param f Fraction
    /// @return Result of multiplication
    friend Fraction operator*(const int &s, const Fraction &f);

    /// @brief Divide fraction
    /// @param f Second Fraction
    /// @return Result of division
    Fraction operator/(const Fraction &f) const;

    /// @brief Divide fraction and assign
    /// @param f Second Fraction
    /// @return Result of division
    Fraction &operator/=(const Fraction &f);

    /// @brief Divide fraction by integer
    /// @param s Scale value
    /// @return Result of division
    Fraction operator/(const int &s) const;

    /// @brief Divide fraction by integer and assign
    /// @param s Scale value
    /// @return Result of division
    Fraction &operator/=(const int &s);

    /// @brief Right-side fraction division by integer
    /// @param s Integer value
    /// @param f Fraction
    /// @return Result of division
    friend Fraction operator/(const int &s, const Fraction &f);

    /// @brief Print fraction
    /// @param os ostream
    /// @param f Fraction
    /// @return Given stream with fraction
    friend std::ostream &operator<<(std::ostream &os, const Fraction &f);
};