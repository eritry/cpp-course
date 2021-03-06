#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include "bigint_vector.h"
#include <functional>

struct big_integer {
    big_integer();

    big_integer(big_integer const &other);

    big_integer(int a);

    explicit big_integer(const bigint_vector& num, bool f);

    explicit big_integer(std::string const &str);

    big_integer(uint a);

    ~big_integer();

    big_integer &operator=(big_integer const &other);

    big_integer &operator=(big_integer &&other);

    big_integer &operator+=(big_integer const &rhs); //
    big_integer &operator-=(big_integer const &rhs);//
    big_integer &operator*=(big_integer const &rhs);//
    big_integer &operator/=(big_integer const &rhs);//
    big_integer &operator%=(big_integer const &rhs);//

    big_integer &operator&=(big_integer const &rhs);//
    big_integer &operator|=(big_integer const &rhs);//
    big_integer &operator^=(big_integer const &rhs);//

    big_integer &operator<<=(int rhs);//
    big_integer &operator>>=(int rhs);//

    big_integer operator+() const;//
    big_integer operator-() const;//
    big_integer operator~() const;//

    big_integer &operator++();//
    const big_integer operator++(int);//

    big_integer &operator--();//
    const big_integer operator--(int);//

    friend bool operator==(big_integer const &a, big_integer const &b);//
    friend bool operator!=(big_integer const &a, big_integer const &b);//
    friend bool operator<(big_integer const &a, big_integer const &b);//
    friend bool operator>(big_integer const &a, big_integer const &b);//
    friend bool operator<=(big_integer const &a, big_integer const &b);//
    friend bool operator>=(big_integer const &a, big_integer const &b);//

    friend std::string to_string(big_integer const &a);//
    friend big_integer operator+(const big_integer &a, big_integer const &b);

    friend big_integer operator*(const big_integer &a, big_integer const &b);

    friend big_integer operator/(const big_integer &a, big_integer const &b);

    template<typename Operation>
    friend big_integer bit_operation_generator(const big_integer &a, big_integer const &b, Operation operation);

    friend big_integer operator<<(big_integer a, int b);

    friend big_integer operator>>(big_integer a, int b);

    friend big_integer operator|(const big_integer &a, uint b);

    friend big_integer operator*(const big_integer &a, uint b);


private:
    bigint_vector digits;
    bool sign;

    size_t size() const;

    void pop_first_zeros();

    uint zero() const;

    void invert_sign();

    big_integer abs() const;

    uint get_digit(size_t i) const;

    uint get_digit_or_max(size_t i) const;

    void shift(int rhs);
};

big_integer operator+(const big_integer &a, big_integer const &b);//
big_integer operator-(const big_integer &a, big_integer const &b);//
big_integer operator*(const big_integer &a, big_integer const &b);//
big_integer operator/(const big_integer &a, big_integer const &b);

big_integer operator%(const big_integer &a, big_integer const &b);

big_integer operator&(const big_integer &a, big_integer const &b);//
big_integer operator|(const big_integer &a, big_integer const &b);//
big_integer operator^(const big_integer &a, big_integer const &b);//

big_integer operator<<(big_integer a, int b);//
big_integer operator>>(big_integer a, int b);//

bool operator==(big_integer const &a, big_integer const &b);//
bool operator!=(big_integer const &a, big_integer const &b);//
bool operator<(big_integer const &a, big_integer const &b);//
bool operator>(big_integer const &a, big_integer const &b);//
bool operator<=(big_integer const &a, big_integer const &b);//
bool operator>=(big_integer const &a, big_integer const &b);//


big_integer operator|(const big_integer &a, uint b);
big_integer operator*(const big_integer &a, uint b);

std::string to_string(big_integer const &a);//
#endif // BIG_INTEGER_H
