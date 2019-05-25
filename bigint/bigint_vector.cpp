#include "bigint_vector.h"
#include <memory>
#include <algorithm>
#include <cassert>

bigint_vector::bigint_vector(int curlen, int value) {
    if (curlen > 1) {
        elements = std::make_shared<std::vector<uint>>(curlen, value);
    } else if (curlen == 1) {
        element = value;
    }
    len = curlen;
}

uint bigint_vector::size() const {
    return len;
}

bigint_vector::bigint_vector(int curlen) {
    if (curlen > 1) {
        elements = std::make_shared<std::vector<uint>>(curlen);
    }
    len = curlen;
}

uint bigint_vector::operator[](size_t ind) const {
    if (small()) {
        return element;
    }
    return elements->operator[](ind);
}

uint &bigint_vector::operator[](size_t ind) {
    if (small()) {
        return element;
    }
    unique();
    return elements->operator[](ind);
}

uint bigint_vector::back() const {
    if (small()) {
        return element;
    }
    return elements->back();
}

uint &bigint_vector::back() {
    if (small()) {
        return element;
    }
    unique();
    return elements->back();
}

void bigint_vector::resize(size_t curlen) {
    if (small()) {
        if (curlen > 1) {
            elements = std::make_shared<std::vector<uint>>(curlen, element);
        }
    } else {
        if (curlen > 1) {
            unique();
            elements->resize(curlen);
        } else if (curlen == 1) {
            uint tmp = *elements->begin();
            elements.reset();
            element = tmp;
        } else {
            elements.reset();
        }
    }
    len = curlen;
}

void bigint_vector::push_back(uint value) {
    if (len == 0) {
        element = value;
    } else if (len == 1) {
        elements = std::make_shared<std::vector<uint>>(1, element);
        elements->push_back(value);
    } else {
        unique();
        elements->push_back(value);
    }
    len++;
}

void bigint_vector::reverse() {
    if (!small()) {
        std::reverse(elements->begin(), elements->end());
    }
}

void bigint_vector::pop_back() {
    if (len > 2) {
        unique();
        elements->pop_back();
    } else if (len == 2) {
        uint tmp = *elements->begin();
        elements.reset();
        element = tmp;
    } else {
        element = 0;
    }
    len--;
}

void bigint_vector::insert_begin(uint cnt) {
    if (small()) {
        if (cnt > 0) {
            uint tmp = element;
            elements = std::make_shared<std::vector<uint>>(cnt + 1);
            elements->back() = tmp;
        }
    } else {
        unique();
        elements->insert(elements->begin(), cnt, 0);
    }
    len += cnt;
}

void bigint_vector::erase_begin(uint cnt) {
    if (!small()) {
        if (len - cnt > 1) {
            unique();
            elements->erase(elements->begin(), elements->begin() + cnt);
        } else {
            element = *elements->begin();
            elements.reset();
        }
    }
    len -= cnt;
}

bool operator==(bigint_vector const &a, bigint_vector const &b) {
    if (a.small() != b.small()) {
        return false;
    }
    if (a.small()) {
        return a.element == b.element;
    }
    return *a.elements == *b.elements;
}

void bigint_vector::unique() {
    if (!elements.unique()) {
        elements = std::make_shared<std::vector<uint>>(*elements);
    }
}

bool bigint_vector::small() const {
    return len <= 1;
}

bigint_vector &bigint_vector::operator=(bigint_vector const &other) {
    if (!small()) {
        elements.reset();
    }
    if (other.small()) {
        element = other.element;
    } else {
        elements = other.elements;
    }
    len = other.len;
    return *this;
}

bigint_vector::bigint_vector() {
    len = 0;
    element = 0;
}

bigint_vector::~bigint_vector() {
    if (!small()) {
        elements.reset();
    }
}

uint* bigint_vector::data() {
    if (small()) {
        return &element;
    }
    unique();
    return elements->data();
}

const uint* bigint_vector::data() const {
    if (small()) {
        return const_cast<uint*>(&element);
    }
    return elements->data();
}
