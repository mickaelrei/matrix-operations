#include <include/fraction.hpp>
#include <cassert>

#define AUTO_REDUCE_FRACTIONS

/// @brief Finds GCD (Greatest Common Divisor) of two integers
/// @param a First integer
/// @param b Second integer
/// @return Resulting GCD
/// Based on: https://en.wikipedia.org/wiki/Euclidean_algorithm
int64_t gcd(int64_t a, int64_t b)
{
    int64_t t = b;
    while (b != 0)
    {
        b = a % b;
        a = t;
        t = b;
    }

    return a;
}

Fraction::Fraction()
    : Fraction{1, 1} {}

Fraction::Fraction(const int64_t &numerator)
    : Fraction{numerator, 1} {}

Fraction::Fraction(const Fraction &f)
    : Fraction(f.numerator, f.denominator) {}

Fraction::Fraction(std::array<int64_t, 2> &data)
    : Fraction(data[0], data[1]) {}

Fraction::Fraction(const int64_t &numerator, const int64_t &denominator)
    : numerator{numerator},
      denominator{denominator}
{
    // Denominator can't be zero
    assert((denominator != 0) && "Denominator can't be zero");
}

Fraction::~Fraction()
{
    numerator = 0;
    denominator = 0;
}

Fraction Fraction::inverse()
{
    // Numerator can't be zero
    assert((numerator != 0) && "Numerator can't be zero");
    return Fraction{denominator, numerator};
}

float Fraction::eval()
{
    assert((denominator != 0) && "Can't eval fraction with denominator zero");
    
    return (float)numerator / (float)denominator;
}

void Fraction::reduce()
{
    const int64_t s = gcd(numerator, denominator);
    // If for any reason GCD was zero, exit
    if (s == 0)
    {
        printf("GCD was zero for fraction %ld/%ld\n", numerator, denominator);
        return;
    }
    numerator /= s;
    denominator /= s;

    // Flip signs if needed
    if (denominator < 0)
    {
        numerator *= -1;
        denominator *= -1;
    }
}

Fraction &Fraction::operator=(const Fraction &f)
{
    numerator = f.numerator;
    denominator = f.denominator;
    return *this;
}

bool Fraction::operator==(const Fraction &f) const
{
    return numerator * f.denominator == denominator * f.numerator;
}

bool Fraction::operator!=(const Fraction &f) const
{
    return !(*this == f);
}

Fraction Fraction::operator+(const Fraction &f) const
{
    Fraction tmp{*this};
    tmp += f;
    return tmp;
}

Fraction &Fraction::operator+=(const Fraction &f)
{
    numerator = numerator * f.denominator + denominator * f.numerator;
    denominator *= f.denominator;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction Fraction::operator+(const int64_t &s) const
{
    Fraction tmp{*this};
    tmp += s;
    return tmp;
}

Fraction &Fraction::operator+=(const int64_t &s)
{
    numerator += denominator * s;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction operator+(const int64_t &i, const Fraction &f)
{
    return f + i;
}

Fraction Fraction::operator-(const Fraction &f) const
{
    Fraction tmp{*this};
    tmp -= f;
    return tmp;
}

Fraction &Fraction::operator-=(const Fraction &f)
{
    numerator = numerator * f.denominator - denominator * f.numerator;
    denominator *= f.denominator;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction Fraction::operator-(const int64_t &s) const
{
    Fraction tmp{*this};
    tmp -= s;
    return tmp;
}

Fraction &Fraction::operator-=(const int64_t &s)
{
    numerator -= denominator * s;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction operator-(const int64_t &s, const Fraction &f)
{
    return f - s;
}

Fraction Fraction::operator-() const
{
    return {-numerator, denominator};
}

Fraction Fraction::operator*(const Fraction &f) const
{
    Fraction tmp{*this};
    tmp *= f;
    return tmp;
}

Fraction &Fraction::operator*=(const Fraction &f)
{
    numerator *= f.numerator;
    denominator *= f.denominator;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction Fraction::operator*(const int64_t &s) const
{
    Fraction tmp{*this};
    tmp *= s;
    return tmp;
}

Fraction &Fraction::operator*=(const int64_t &s)
{
    numerator *= s;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction operator*(const int64_t &s, const Fraction &f)
{
    return f * s;
}

Fraction Fraction::operator/(const Fraction &f) const
{
    Fraction tmp{*this};
    tmp /= f;
    return tmp;
}

Fraction &Fraction::operator/=(const Fraction &f)
{
    // Can't divide by zero
    assert((f.numerator != 0) && "Can't divide by fraction with numerator zero");

    numerator *= f.denominator;
    denominator *= f.numerator;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction Fraction::operator/(const int64_t &s) const
{
    Fraction tmp{*this};
    tmp /= s;
    return tmp;
}

Fraction &Fraction::operator/=(const int64_t &s)
{
    // Can't divide by zero
    assert((s != 0) && "Can't divide by literal zero");

    denominator *= s;

#ifdef AUTO_REDUCE_FRACTIONS
    reduce();
#endif

    return *this;
}

Fraction operator/(const int64_t &s, const Fraction &f)
{
    return Fraction{s} / f;
}

std::ostream &operator<<(std::ostream &os, const Fraction &f)
{
    os << f.numerator;
    if (f.numerator != 0 && f.denominator != 1)
    {
        os << "/" << f.denominator;
    }

    return os;
}