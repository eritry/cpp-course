//
// Created by erika on 15.06.19.
//

#ifndef EXAM_VECTOR_H
#define EXAM_VECTOR_H

#include <variant>
#include <memory>
#include <stdexcept>
#include <cstring>

template<typename T>
struct pointer {
    struct storage {
        size_t capacity, refs_count;
        T *elements;
    };

    void allocate(size_t size) {
        data = reinterpret_cast<storage *>(operator new(sizeof(storage) + size * sizeof(T)));
        data->refs_count = 1;
        data->capacity = size;
        data->elements = (T *) ((char *) data + sizeof(storage));

    }

    void increase_refs() {
        data->refs_count++;
    }

    void decrease_refs(size_t cnt) {
        data->refs_count--;
        if (!data->refs_count) {
            for (size_t i = 0; i < cnt; i++) data->elements[i].~T();
            operator delete(data);
        }
    }

    storage *data;
};

template<typename T>
struct vector {
public:
    typedef T value_type;

    typedef T *iterator;
    typedef const T *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


    T &get_small() const noexcept {
        return const_cast<T &>(std::get<1>(data_));
    }

    T *get_big() const noexcept {
        return std::get<2>(data_).data->elements;
    }

    pointer<T>& pointer_data() const noexcept {
        return const_cast<pointer<T>&>(std::get<2>(data_));
    }

    vector() noexcept : size_(0) {}

    vector(vector const &other) {
        size_ = other.size_;
        data_ = other.data_;
        if (!is_small()) pointer_data().increase_refs();
    }

    explicit vector(size_t new_size, const T &value = T()) : size_(new_size) {
        if (new_size == 1) {
            data_ = T(value);
        } else if (new_size > 1) {
            pointer<T> new_data;
            new_data.allocate(new_size);
            for (size_t i = 0; i < new_size; i++) {
                try {
                    new(new_data.data->elements + i) T(value);
                } catch (...) {
                    new_data.decrease_refs(i);
                    throw;
                }
            }
            data_ = new_data;
        }
    }

    template<typename InputIterator>
    vector(InputIterator first, InputIterator last) : vector() {
        while (first != last) {
            push_back(*first);
            first++;
        }
    }

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last) {
        vector(first, last).swap(*this);
    }

    ~vector() noexcept {
        if (!is_small()) pointer_data().decrease_refs(size_);
    }

    vector &operator=(vector const &other) {
        if (this == &other) return *this;

        if (!is_small()) pointer_data().decrease_refs(size_);

        size_ = other.size_;
        data_ = other.data_;

        if (!is_small()) pointer_data().increase_refs();
        return *this;
    }

    const T &operator[](size_t ind) const noexcept {
        if (data_.index() == 1) return get_small();
        return get_big()[ind];
    }

    T &operator[](size_t ind) {
        if (data_.index() == 1) return get_small();
        copy();
        return get_big()[ind];

    }

    T &front() noexcept {
        return operator[](0);
    }

    T &back() noexcept {
        return operator[](size_ - 1);
    }

    const T &front() const noexcept {
        return operator[](0);
    }

    const T &back() const noexcept {
        return operator[](size_ - 1);
    }

    void push_back(const T &value) {
        copy();
        if (size_ > 0 && size_ >= capacity()) {
            vector<T> buffer(*this);
            auto tmp = value;

            buffer.copy();
            buffer.reserve(2 * buffer.capacity());
            new(std::get<pointer<T>>(buffer.data_).data->elements + size_) T(tmp);

            buffer.size_++;
            *this = buffer;
        } else {
            if (is_small()) {
                data_ = T(value);
            } else {
                new(get_big() + size_) T(value);
            }
            size_++;
        }
        
    }

    void pop_back() {
        copy();
        size_--;
        if (!is_small()) get_big()[size_].~T();
    }

    T *data()noexcept {
        if (std::holds_alternative<std::monostate>(data_)) return nullptr;
        if (!is_small()) return get_big();
        return &get_small();
    }

    T const *data() const noexcept {
        if (std::holds_alternative<std::monostate>(data_)) return nullptr;
        if (!is_small()) return get_big();
        return &get_small();
    }

    iterator begin() const noexcept {
        return const_cast<iterator>(data());
    }

    iterator end() const noexcept {
        return const_cast<iterator>(data() + size());
    }

    reverse_iterator rbegin() const noexcept {
        return std::make_reverse_iterator(end());
    }

    reverse_iterator rend() const noexcept {
        return std::make_reverse_iterator(begin());
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    void reserve(size_t new_size) {
        vector<T> buffer(*this);
        buffer.copy();
        if (new_size <= buffer.capacity()) return;

        if (new_size > 1) {
            pointer<T> new_data;
            new_data.allocate(new_size);
            for (size_t i = 0; i < buffer.size_; i++) {
                try {
                    new(new_data.data->elements + i) T(buffer.data()[i]);
                } catch (...) {
                    for (size_t j = 0; j < i; j++) {
                        new_data.data->elements[j].~T();
                    }
                    operator delete(new_data.data);
                    throw;
                }
            }
            if (!buffer.is_small()) {
                std::get<pointer<T>>(buffer.data_).decrease_refs(buffer.size_);
            }
            buffer.data_ = new_data;
        }
        *this = buffer;
    }

    void resize(size_t new_size, const T &value = T()) {
        vector buffer(new_size, value);
        for (size_t i = 0; i != size_ && i != buffer.size_; i++) {
            buffer[i] = operator[](i);
        }
        buffer.swap(*this);

    }

    size_t capacity() const noexcept {
        if (is_small()) return 1;
        return pointer_data().data->capacity;
    }

    void shrink_to_fit() {
        reserve(size_);
    }

    void clear() {
        vector().swap(*this);
    }

    iterator insert(const_iterator pos, T const &val) {
        auto d = pos - begin();
        copy();
        pos = begin() + d;

        if (size_ == 1) {
            push_back(val);
            return begin();
        } else if (size_ == capacity()) {
            auto distance = pos - begin();
            push_back(val);
            pos = begin() + distance;
        } else {
            auto distance = pos - begin();
            push_back(val);
            pos = begin() + distance;
        }

        for (auto it = end() - 1; it != pos; it--) *it = *(it - 1);
        *(begin() + d) = val;
        return begin() + d;
    }

    iterator erase(const_iterator pos) {
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last) {
        auto buffer = *this;
        buffer.copy();

        first -= begin() - buffer.begin();
        last -= begin() - buffer.begin();

        auto f = const_cast<iterator>(first);
        auto l = const_cast<iterator>(last);

        if (l == buffer.end()) {
            size_t dist = f - buffer.begin();
            while (buffer.size() > dist) {
                buffer.pop_back();
            }
            *this = buffer;
            return begin() + dist;
        }

        for (; l != buffer.end(); f++, l++) *f = *l;

        auto dist = f - buffer.begin();
        buffer.resize(size() - (l - f), buffer.front());
        *this = buffer;
        return begin() + dist;
    }

    template<typename U>
    friend void swap(vector<U> &, vector<U> &);

    template<typename U>
    friend bool operator==(vector<U> const &, vector<U> const &) noexcept;

    template<typename U>
    friend bool operator!=(vector<U> const &, vector<U> const &) noexcept;

    template<typename U>
    friend bool operator<(vector<U> const &, vector<U> const &) noexcept;

    template<typename U>
    friend bool operator<=(vector<U> const &, vector<U> const &) noexcept;

    template<typename U>
    friend bool operator>(vector<U> const &, vector<U> const &) noexcept;

    template<typename U>
    friend bool operator>=(vector<U> const &, vector<U> const &) noexcept;

private:
    size_t size_ = 0;
    std::variant<std::monostate, T, pointer<T>> data_;

    void swap(vector<T>& other) {
          if (!other.is_small() && !empty() && is_small()) {
            other.swap(*this);
            return;
        }
        if (other.is_small() && !other.empty() && !is_small()) {
            T cur = other.front();
            other.pop_back();
            for (size_t i = 0; i < size_; i++) {
                other.push_back((*this)[i]);
            }
            while (!empty()) pop_back();
            push_back(cur);
            return;
        }
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    bool is_small() const noexcept {
        return !std::holds_alternative<pointer<T>>(data_);
    }

    void copy() {
        if (is_small() || pointer_data().data->refs_count <= 1) return;

        T *cur_data = data();
        pointer<T> new_data;
        new_data.allocate(capacity());

        for (size_t i = 0; i < size_; i++) {
            try {
                new(new_data.data->elements + i) T(cur_data[i]);
            } catch (...) {
                for (size_t j = 0; j < i; j++) new_data.data->elements[j].~T();
                operator delete(new_data.data);
                throw;
            }
        }
        pointer_data().decrease_refs(size_);
        data_ = new_data;
    }
};


template<typename T>
void swap(vector<T> &first, vector<T> &second) {
    first.swap(second);
}

template<typename T>
bool operator==(vector<T> const &first, vector<T> const &second) noexcept {
    if (first.size() != second.size()) return false;
    for (size_t i = 0; i < first.size(); i++) {
        if (first[i] != second[i]) return false;
    }
    return true;
}

template<typename T>
bool operator!=(vector<T> const &first, vector<T> const &second) noexcept {
    return !(first == second);
}

template<typename T>
bool operator<(vector<T> const &first, vector<T> const &second) noexcept {
    for (size_t i = 0; i < std::min(first.size(), second.size()); i++) {
        if (first[i] == second[i]) continue;
        return (first[i] < second[i]);
    }
    return first.size() < second.size();
}

template<typename T>
bool operator>(vector<T> const &first, vector<T> const &second) noexcept {
    return (second < first);
}

template<typename T>
bool operator>=(vector<T> const &first, vector<T> const &second) noexcept {
    return !(first < second);
}

template<typename T>
bool operator<=(vector<T> const &first, vector<T> const &second) noexcept {
    return !(first > second);
}

#endif 