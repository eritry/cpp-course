#include "big_integer.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <string>
#include <cmath>

const bool PLUS = false;
const bool MINUS = true;

const size_t SIZE = 9;
const unsigned int BLOCK = (int)1e9;

const unsigned int ZERO_PLUS = 0;
const unsigned int ZERO_MINUS = static_cast<const unsigned int>(std::numeric_limits<unsigned int>::max());

const unsigned int MAX = UINT32_MAX;
const size_t SIZEOF_INT = static_cast<const size_t>(std::numeric_limits<unsigned int>::digits);
//________________________________________________________

big_integer::big_integer() : digits(1, 0), sign(PLUS) {}
big_integer::big_integer(int a) : digits(1, a), sign(a < 0) {}
big_integer::big_integer(big_integer const& other) = default;
big_integer::big_integer(unsigned int a) : digits(1, a), sign(PLUS) {}

big_integer::big_integer(std::string const& str) : big_integer() {
    bool this_sign = str[0] == '-';
    size_t i = (this_sign ? 1 : 0);
    for (; i < str.size(); i += SIZE) {
        unsigned int cur_size = std::min<unsigned int>(SIZE, str.size() - i);
        std::string rest = str.substr(i, cur_size);
        if (i + SIZE > str.size()) {
            int pow10 = 1;
            for (size_t p = 0; p < cur_size; p++) pow10 *= 10;
            *this *= pow10;
        } else {
            *this *= BLOCK;
        }
        *this += static_cast<unsigned int>(std::stoul(rest));
    }
    pop_first_zeros();
    if (this_sign) {
        this->invert_sign();
    }
}

big_integer::big_integer(std::vector<unsigned int> num, bool f) : digits(std::move(num)), sign(f){
    pop_first_zeros();
}

big_integer &big_integer::operator=(big_integer const& other) = default;
big_integer &big_integer::operator=(big_integer &&other) = default;

big_integer::~big_integer() = default;

//________________________________________________________

big_integer &big_integer::operator+=(big_integer const& rhs) {
    *this = *this + rhs;
    return *this;
}
big_integer &big_integer::operator-=(big_integer const& rhs) {
    *this = *this - rhs;
    return *this;
}
big_integer &big_integer::operator*=(big_integer const& rhs) {
    *this = *this * rhs;
    return *this;
}
big_integer &big_integer::operator/=(big_integer const& rhs) {
    *this = *this / rhs;
    return *this;
}
big_integer &big_integer::operator%=(big_integer const& rhs) {
    *this = *this % rhs;
    return *this;
}
big_integer &big_integer::operator&=(big_integer const& rhs) {
    *this = *this & rhs;
    return *this;
}
big_integer &big_integer::operator|=(big_integer const& rhs) {
    *this = *this | rhs;
    return *this;
}
big_integer &big_integer::operator^=(big_integer const& rhs) {
    *this = *this ^ rhs;
    return *this;
}
big_integer &big_integer::operator<<=(int rhs) {
    *this = *this << rhs;
    return *this;
}
big_integer &big_integer::operator>>=(int rhs) {
    *this = *this >> rhs;
    return *this;
}
//________________________________________________________

big_integer big_integer::operator-() const {
    return ~*this + 1;
}
big_integer big_integer::operator+() const {
    return *this;
}
big_integer big_integer::operator~() const {
    std::vector<unsigned int> ans(digits.size());
    for (size_t i = 0; i < digits.size(); i++) {
        ans[i] = ~digits[i];
    }
    return big_integer(std::move(ans), !sign);
}
//________________________________________________________

big_integer &big_integer::operator++() {
    *this += 1;
    return *this;
}
big_integer big_integer::operator++(int a) {
    *this += 1;
    return *this;
}
big_integer &big_integer::operator--() {
    *this -= 1;
    return *this;
}
big_integer big_integer::operator--(int a) {
    *this -= 1;
    return *this;
}
//________________________________________________________

big_integer operator+(const big_integer& a, big_integer const& b) {
    unsigned long long carry = 0;
    size_t length = std::max(a.size(), b.size()) + 1;

    std::vector<unsigned int> ans(length + 1);

    for (size_t i = 0; i <= length; i++) {
        unsigned long long new_carry = carry + a.get_digit_or_max(i) + b.get_digit_or_max(i);
        carry = new_carry > MAX;
        ans[i] = static_cast<unsigned int>(new_carry);
    }

    bool sign = (ans.back() >> 31) > 0;
    return big_integer(std::move(ans), sign);
}

big_integer operator-(big_integer const& a, big_integer const& b) {
    return a + (-b);
}

big_integer operator*(big_integer a, big_integer const& b) {
    std::vector<unsigned int> ans(a.size() + b.size());
    big_integer positive_a = a.abs();
    big_integer positive_b = b.abs();

    for (size_t i = 0; i < a.size(); i++) {
        unsigned long long carry = 0;
        for (size_t j = 0; j < b.size(); j++) {
            size_t ind = i + j;
            carry += static_cast<unsigned long long>(ans[ind]) +
                    static_cast<unsigned long long>(positive_a.get_digit(i)) * static_cast<unsigned long long>(positive_b.get_digit(j));
            ans[ind] = static_cast<unsigned int>(carry & MAX);
            carry >>= 32;
        }
        ans[i + b.size()] += static_cast<unsigned int>(carry);
     }
    big_integer ret(std::move(ans), PLUS);
    return (a.sign ^ b.sign ? -ret : ret);
}

big_integer operator/(big_integer a, big_integer const& b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    big_integer positive_a = a.abs();
    big_integer positive_b = b.abs();
    if (positive_a < positive_b) return 0;

    big_integer ans;
    ans.digits.resize(positive_a.size());

    if (positive_b.digits.back() < MAX / 2) {
        positive_a *= MAX / (positive_b.digits.back() + 1);
        positive_b *= MAX / (positive_b.digits.back() + 1);
    }

    big_integer res;
    for (size_t i = positive_a.size(); i > 0; i--) {
        res = (res << SIZEOF_INT) | positive_a.get_digit(i - 1);
        res.pop_first_zeros();

        if (res.size() < positive_b.size()) {
            ans.digits.push_back(0);
            continue;
        }

        if (res.size() == positive_b.size()) {
            res.digits.push_back(0);
        }

        unsigned long long cur = res.digits.back();
        unsigned long long prev = res.get_digit(res.size() - 2);
        cur = (cur << SIZEOF_INT) | prev;
        cur /= static_cast<unsigned long long>(positive_b.digits.back());

        big_integer un;
        un.digits.resize(2);
        un.digits[0] = static_cast<unsigned int>(cur);
        un.digits[1] = static_cast<unsigned int>(cur >> SIZEOF_INT);

        un *= positive_b;

        while (cur > 0 && un > res) {
            cur--;
            un -= positive_b;
        }

        ans.digits.push_back(static_cast<unsigned int>(cur));
        res -= un;

    }
    std::reverse(ans.digits.begin(), ans.digits.end());
    ans.pop_first_zeros();

    if (a.sign ^ b.sign) ans.invert_sign();
    return ans;
}

big_integer operator%(big_integer a, big_integer const& b) {
    return a - a / b * b;
}

//________________________________________________________

struct operation_and
{
    template <typename T>
    T operator()(T a, T b) const
    {
        return a & b;
    }
};

struct operation_or
{
    template <typename T>
    T operator()(T a, T b) const
    {
        return a | b;
    }
};

struct operation_xor
{
    template <typename T>
    T operator()(T a, T b) const
    {
        return a ^ b;
    }
};

template <typename Operation>
big_integer bit_operation_generator(big_integer a, big_integer const& b, Operation operation) {
    size_t length = std::max(a.size(), b.size());
    std::vector<unsigned int> ans(length);
    for (size_t i = 0; i < length; i++) {
        ans[i] = operation(a.get_digit_or_max(i), b.get_digit_or_max(i));
    }
    return big_integer(std::move(ans), operation(a.sign, b.sign));
}
big_integer operator&(big_integer a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_and());
}
big_integer operator|(big_integer a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_or());
}
big_integer operator^(big_integer a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_xor());
}
//________________________________________________________

big_integer operator<<(big_integer a, int b) {
    if (b < 0) return a >> (-b);
    int cnt = b / 32;
    if (cnt) a.shift(cnt);

    unsigned int big_shift = b % 32;
    unsigned int small_shift = 32 - big_shift;
    if (big_shift) {
        a.digits.push_back(a.zero());
        for (size_t i = a.size(); i > 0; i--) {
            if (i < a.size()) {
                a.digits[i] += a.get_digit(i - 1) >> small_shift;
            }
            a.digits[i - 1] <<= big_shift;
        }
    }
    a.pop_first_zeros();
    return a;
}
big_integer operator>>(big_integer a, int b) {
    if (b < 0) return a << (-b);
    int cnt = b / 32;
    if (cnt) a.shift(-cnt);

    unsigned int big_shift = b % 32;
    unsigned int small_shift = 32 - big_shift;
    if (big_shift) {
        unsigned int cur = a.zero();
        for (size_t i = 0; i < a.size(); i++) {
            if (i > 0) {
                a.digits[i - 1] += a.get_digit(i) << small_shift;
            }
            a.digits[i] >>= big_shift;
        }
        a.digits.back() += cur << small_shift;
    }
    a.pop_first_zeros();
    return a;
}

void big_integer::shift(int rhs) {
    if (rhs > 0) {
        digits.insert(digits.begin(), rhs, 0);
    } else {
        digits.erase(digits.begin(), digits.begin() - rhs);
    }
}
//________________________________________________________

bool operator==(big_integer const& a, big_integer const& b) {
    return a.sign == b.sign && a.digits == b.digits;
}
bool operator!=(big_integer const& a, big_integer const& b) {
    return !(a == b);
}
bool operator<(big_integer const& a, big_integer const& b) {
    if (a.sign != b.sign) return (a.sign > b.sign);
    if (a.size() != b.size()) return (a.size() < b.size());
    for (size_t i = a.size(); i > 0; i--) {
        if (a.get_digit(i - 1) != b.get_digit(i - 1)) {
            return a.get_digit(i - 1) < b.get_digit(i - 1);
        }
    }
    return false;
}
bool operator>(big_integer const& a, big_integer const& b) {
    return b < a;
}
bool operator<=(big_integer const& a, big_integer const& b) {
    return (a < b || a == b);
}
bool operator>=(big_integer const& a, big_integer const& b) {
    return (a > b || a == b);
}
//________________________________________________________

std::string to_string(big_integer const& a) {
    std::string ans;
    auto mod = BLOCK;
    big_integer positive_a = a.abs();
    while (positive_a != 0) {
        big_integer digit = positive_a % mod;
        unsigned int new_digit = digit.get_digit_or_max(0);
        positive_a /= mod;
        for (size_t i = 0; i < 9; i++) {
            ans += '0' + new_digit % 10;
            new_digit /= 10;
        }
    }

    if (ans.empty()) return "0";
    while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
    if (a.sign) ans += "-";
    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    return s << to_string(a);
}

//________________________________________________________

void big_integer::pop_first_zeros() {
    while (size() > 1 && digits.back() == zero()) {
        digits.pop_back();
    }
}

size_t big_integer::size() const {
    return digits.size();
}

unsigned int big_integer::zero() const {
    return (!sign ? ZERO_PLUS : ZERO_MINUS);
}

void big_integer::invert_sign() {
    sign ^= true;
    for (size_t i = 0; i < size(); i++) {
        digits[i] = ~digits[i];
    }
    (*this)++;
    pop_first_zeros();
}

unsigned int big_integer::get_digit(size_t i) const {
    return digits[i];
}

unsigned int big_integer::get_digit_or_max(size_t i) const {
    if (i >= digits.size()) {
        return (sign ? MAX : 0);
    } else {
        return digits[i];
    }
}

big_integer big_integer::abs() const {
    return (sign ? -*this : *this);
}
