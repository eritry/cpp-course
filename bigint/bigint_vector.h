#ifndef BIGINT_BIGINT_VECTOR_H
#define BIGINT_BIGINT_VECTOR_H

#include <memory>
#include <vector>

typedef uint32_t uint;
typedef uint64_t ull;

class bigint_vector {
public:
    explicit bigint_vector(int curlen, int value);

    explicit bigint_vector(int curlen);

    bigint_vector();

    ~bigint_vector();

    uint size() const;

    uint operator[](size_t ind) const;

    uint &operator[](size_t ind);

    uint back() const;

    uint &back();

    void resize(size_t curlen);

    void push_back(uint value);

    void reverse();

    void pop_back();

    void insert_begin(uint cnt);

    void erase_begin(uint cnt);

    friend bool operator==(bigint_vector const &a, bigint_vector const &b);

    bigint_vector& operator=(bigint_vector const &other);

    const uint* data() const;

    uint* data();

private:
    size_t len;

    uint element;
    std::shared_ptr<std::vector<uint>> elements;

    bool small() const;

    void unique();

};

bool operator==(bigint_vector const &a, bigint_vector const &b);

#endif //BIGINT_BIGINT_VECTOR_H
