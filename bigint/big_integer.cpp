#include <utility>

#include "big_integer.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <string>
#include <cmath>

const bool PLUS = false;

const size_t SIZE = 9;
const uint BLOCK = (int)1e9;

const uint ZERO_PLUS = 0;
const uint ZERO_MINUS = static_cast<const uint>(std::numeric_limits<uint>::max());

const uint MAX = UINT32_MAX;
const size_t SIZEOF_INT = static_cast<const size_t>(std::numeric_limits<uint>::digits);
//________________________________________________________

big_integer::big_integer() : digits(1, 0), sign(PLUS) {}
big_integer::big_integer(int a) : digits(1, a), sign(a < 0) {}

big_integer::big_integer(big_integer const& other) {
    digits = other.digits;
    sign = other.sign;
}

big_integer::big_integer(uint a) : digits(1, a), sign(PLUS) {}

big_integer::big_integer(std::string const& str) : big_integer() {
    bool this_sign = str[0] == '-';
    size_t i = (this_sign ? 1 : 0);
    for (; i < str.size(); i += SIZE) {
        size_t cur_size = std::min<size_t>(SIZE, str.size() - i);
        std::string rest = str.substr(i, cur_size);
        if (i + SIZE > str.size()) {
            int pow10 = 1;
            for (size_t p = 0; p < cur_size; p++) pow10 *= 10;
            *this *= pow10;
        } else {
            *this *= BLOCK;
        }
        *this += static_cast<uint>(std::stoul(rest));
    }
    pop_first_zeros();
    if (this_sign) {
        this->invert_sign();
    }
}

big_integer::big_integer(const bigint_vector& num, bool f) {
    digits = num;
    sign = f;
    pop_first_zeros();
}

big_integer &big_integer::operator=(big_integer const& other) {
    digits = other.digits;
    sign = other.sign;
    return *this;
}

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
    bigint_vector ans(digits.size());
    uint* ans_data = ans.data();
    const uint* digits_data = digits.data();
    for (size_t i = 0; i < digits.size(); i++) {
        ans_data[i] = ~digits_data[i];
    }
    return big_integer(ans, !sign);
}
//________________________________________________________

big_integer &big_integer::operator++() {
    *this += 1;
    return *this;
}
const big_integer big_integer::operator++(int a) {
    *this += 1;
    return *this;
}
big_integer &big_integer::operator--() {
    *this -= 1;
    return *this;
}
const big_integer big_integer::operator--(int a) {
    *this -= 1;
    return *this;
}
//________________________________________________________

big_integer operator+(const big_integer& a, big_integer const& b) {
    ull carry = 0;
    size_t length = std::max(a.size(), b.size()) + 1;

    bigint_vector ans(length + 1);

    const uint* a_data = a.digits.data();
    const uint* b_data = b.digits.data();
    uint* ans_data = ans.data();

    uint a_max = a.sign ? MAX : 0;
    uint b_max = b.sign ? MAX : 0;

    for (size_t i = 0; i <= length; i++) {
        ull new_carry = carry + (i < a.size() ? a_data[i] : a_max) + (i < b.size() ? b_data[i] : b_max);
        carry = new_carry > MAX;
        ans_data[i] = static_cast<uint>(new_carry);
    }

    bool sign = (ans_data[length] >> 31) > 0;
    return big_integer(ans, sign);
}

big_integer operator-(big_integer const& a, big_integer const& b) {
    return a + (-b);
}

big_integer operator*(const big_integer& a, big_integer const& b) {
    bigint_vector ans(a.size() + b.size());
    big_integer positive_a = a.abs();
    big_integer positive_b = b.abs();

    const uint* positive_a_data = positive_a.digits.data();
    const uint* positive_b_data = positive_b.digits.data();
    uint* ans_data = ans.data();

    for (size_t i = 0; i < a.size(); i++) {
        ull carry = 0;
        for (size_t j = 0; j < b.size(); j++) {
            size_t ind = i + j;
            carry += static_cast<ull>(ans_data[ind]) +
                     static_cast<ull>(positive_a_data[i]) * static_cast<ull>(positive_b_data[j]);
            ans_data[ind] = static_cast<uint>(carry & MAX);
            carry >>= 32;
        }
        ans[i + b.size()] += static_cast<uint>(carry);
     }
    big_integer ret(ans, PLUS);
    return (a.sign ^ b.sign ? -ret : ret);
}

big_integer operator/(const big_integer& a, big_integer const& b) {
    if (b == 0) throw std::runtime_error("Division by zero");
    big_integer positive_a = a.abs();
    big_integer positive_b = b.abs();
    if (positive_a < positive_b) return 0;

    if (positive_b.digits.back() < MAX / 2) {
        positive_a = positive_a * (MAX / (positive_b.digits.back() + 1));
        positive_b = positive_b * (MAX / (positive_b.digits.back() + 1));
    }

    big_integer res, un;
    
    const uint* positive_a_data = positive_a.digits.data();
    uint divisor = positive_b.digits.back();

    big_integer ans;
    ans.digits.resize(positive_a.size());
    uint* ans_data = ans.digits.data();

    for (size_t i = positive_a.size(), ind = 0; i > 0; i--, ind++) {
        res = (res << SIZEOF_INT);
        res.digits[0] |= positive_a_data[i - 1];

        if (res.size() < positive_b.size()) {
            ans_data[ind] = 0;
            continue;
        }

        if (res.size() == positive_b.size()) {
            res.digits.push_back(0);
        }

        ull cur = res.digits.back();
        ull prev = res.get_digit(res.size() - 2);
        cur = (cur << SIZEOF_INT) | prev;
        cur /= static_cast<ull>(divisor);

        un = positive_b * static_cast<uint>(cur > MAX ? MAX : cur);

        while (cur > 0 && un > res) {
            cur--;
            un -= positive_b;
        }

        ans_data[ind] = cur;
        res -= un;

    }
    ans.digits.reverse();
    ans.pop_first_zeros();

    if (a.sign ^ b.sign) ans.invert_sign();
    return ans;
}

big_integer operator%(const big_integer& a, big_integer const& b) {
    return a - a / b * b;
}

//________________________________________________________

struct operation_and {
    template <typename T>
    T operator()(T a, T b) const {
        return a & b;
    }
};

struct operation_or {
    template <typename T>
    T operator()(T a, T b) const {
        return a | b;
    }
};

struct operation_xor {
    template <typename T>
    T operator()(T a, T b) const {
        return a ^ b;
    }
};

template <typename Operation>
big_integer bit_operation_generator(const big_integer& a, big_integer const& b, Operation operation) {
    size_t length = std::max(a.size(), b.size());
    bigint_vector ans(length);
    for (size_t i = 0; i < length; i++) {
        ans[i] = operation(a.get_digit_or_max(i), b.get_digit_or_max(i));
    }
    return big_integer(ans, operation(a.sign, b.sign));
}
big_integer operator&(const big_integer& a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_and());
}
big_integer operator|(const big_integer& a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_or());
}
big_integer operator^(const big_integer& a, big_integer const& b) {
    return bit_operation_generator(a, b, operation_xor());
}
//________________________________________________________

big_integer operator<<(big_integer a, int b) {
    if (b < 0) return a >> (-b);
    int cnt = b / 32;
    if (cnt) a.shift(cnt);

    uint big_shift = b % 32;
    uint small_shift = 32 - big_shift;
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

    uint big_shift = b % 32;
    uint small_shift = 32 - big_shift;
    if (big_shift) {
        uint cur = a.zero();
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
        digits.insert_begin(rhs);
    } else {
        digits.erase_begin(-rhs);
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
big_integer operator|(big_integer const& a, uint b) {
    auto res = a;
    res.digits[0] |= b;
    return res;
}

big_integer operator*(big_integer const& a, uint b) {
    auto res = a;
    if (a.sign) {
        res = -res;
    }
    res.digits.push_back(0);

    uint* res_data = res.digits.data();

    ull cur = 0;
    for (size_t i = 0; i < res.size(); i++) {
        cur += (ull)res_data[i] * b;
        res_data[i] = cur & MAX;
        cur >>= SIZEOF_INT;
    }
    if (a.sign) {
        res = -res;
    }
    res.pop_first_zeros();
    return res;
}

//________________________________________________________

std::string to_string(big_integer const& a) {
    std::string ans;
    auto mod = BLOCK;
    big_integer positive_a = a.abs();
    while (positive_a != 0) {
        big_integer digit = positive_a % mod;
        uint new_digit = digit.get_digit_or_max(0);
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

//________________________________________________________

void big_integer::pop_first_zeros() {
    while (size() > 1 && digits.back() == zero()) {
        digits.pop_back();
    }
}

size_t big_integer::size() const {
    return digits.size();
}

uint big_integer::zero() const {
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

uint big_integer::get_digit(size_t i) const {
    return digits[i];
}

uint big_integer::get_digit_or_max(size_t i) const {
    if (i >= digits.size()) {
        return (sign ? MAX : 0);
    } else {
        return digits[i];
    }
}

big_integer big_integer::abs() const {
    return (sign ? -*this : *this);
}
