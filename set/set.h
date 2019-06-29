#ifndef SET_SET_H
#define SET_SET_H
#include <iterator>

template <typename T>
struct set {
private:
    struct base_node {
        base_node *l = nullptr;
        base_node *r = nullptr;
        base_node *parent = nullptr;

        base_node() = default;
        ~base_node() = default;
    };
    struct node : public base_node {
        T data;
        explicit node(T const& data) : data(data) {}
    };

    mutable base_node fake;

    base_node* root() const {
        return &fake;
    }

public:
    template<typename U>
struct set_iterator : public std::iterator<std::bidirectional_iterator_tag, U> {
        friend class set<T>;
    public:
        set_iterator() : p(nullptr) {}

        const set_iterator operator++(int) {
            set_iterator old(p);
            ++(*this);
            return old;
        }

        const set_iterator operator--(int) {
            set_iterator old(p);
            --(*this);
            return old;
        }

        bool operator==(const set_iterator& other) const {
            return p == other.p;
        }

        bool operator!=(const set_iterator& other) const {
            return !(p == other.p);
        }

        U& operator*() const {
            return (static_cast<node*>(p)->data);
        }
        U const* operator->() const {
            return &(static_cast<node*>(p)->data);
        }

        set_iterator &operator++() {
            p = next(p);
            return *this;
        }

        set_iterator &operator--() {
            p = prev(p);
            return *this;
        }


    private:
        explicit set_iterator(base_node *p) : p(p) {}
        base_node* get() {
            return p;
        }
    private:
        base_node *p;
    };

    using value_type = T;
    typedef set_iterator<const T> iterator;
    typedef set_iterator<const T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    set() noexcept = default;
    ~set() {
        clear();
    }

    set(set const& other) : set() {
        for (auto const &e : other) {
            insert(e);
        }
    }

    set& operator=(set const& other) {
        set s(other);
        swap(s, *this);
        return *this;
    }

    bool empty() const noexcept {
        return root()->l == nullptr;
    }

    void clear() noexcept {
        for (auto it = begin(); it != end(); ) {
            it = erase(it);
        }
    }

    const_iterator begin() const {
        auto v = root();
        for (; v->l != nullptr; v = v->l) {}
        return const_iterator(v);
    }

    iterator begin() {
        auto v = root();
        for (; v->l != nullptr; v = v->l) {}
        return iterator(v);
    }

    const_iterator end() const {
        return const_iterator(root());
    }

    iterator end() {
        return iterator(root());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    template<typename U>
    friend void swap(set<U> &first, set<U>& second) noexcept;

    std::pair<iterator, bool> insert(value_type const& value) {
        if (empty()) {
            root()->l = new node(value);
            root()->l->parent = root();
            return {const_iterator(root()->l), true};
        }
        
        base_node* cur = root()->l;
        while (cur != nullptr) {
            T const &x = static_cast<node*>(cur)->data;
            if (x < value) {
                if (cur->r != nullptr) {
                    cur = cur->r;
                    continue;
                }
                cur->r = new node(value);
                cur->r->parent = cur;
                return {const_iterator(cur->r), true};
            }
            if (value < x) {
                if (cur->l != nullptr) {
                    cur = cur->l;
                    continue;
                }
                cur->l = new node(value);
                cur->l->parent = cur;
                return {const_iterator(cur->l), true};
            }
            return {const_iterator(cur), false};
        }
        return {end(), false};
    }

    iterator erase(const_iterator pos) noexcept {
        iterator ans(pos);
        ++ans;

        base_node* v = pos.p;
        base_node* cur = v->parent;

        if (v->l != nullptr && v->r != nullptr) {
            auto left = get_down(v->r);

            base_node *new_ref = nullptr;
            if (!left->l && left->r) new_ref = left->r;
            if (left->l && !left->r) new_ref = left->l;

            if (left->parent->l == left) left->parent->l = new_ref;
            else left->parent->r = new_ref;

            if (!left->l && left->r) left->r->parent = left->parent;
            if (left->l && !left->r) left->l->parent = left->parent;

            if (v->parent->l == v) v->parent->l = left;
            else v->parent->r = left;

            if (v->r) v->r->parent = left;
            if (v->l) v->l->parent = left;

            left->parent = v->parent;
            left->l = v->l;
            left->r = v->r;
        } else {
            base_node *new_ref = nullptr;
            if (!v->l && v->r) new_ref = v->r;
            if (v->l && !v->r) new_ref = v->l;

            if (v == cur->l) cur->l = new_ref;
            else cur->r = new_ref;

            if (!v->l && v->r) v->r->parent = cur;
            if (v->l && !v->r) v->l->parent = cur;
        }

        v->parent = nullptr;
        v->r = nullptr;
        v->l = nullptr;
        delete static_cast<node*>(v);

        return ans;
    }

    base_node* find(base_node *v, T const& pos) const {
        if (v == nullptr) {
            return nullptr;
        }

        T const &x = static_cast<node*>(v)->data;

        if (pos < x) return find(v->l, pos);
        if (pos > x) return find(v->r, pos);
        if (!(pos < x) && !(x < pos)) return v;
    }

    const_iterator find(value_type const& pos) const {
        auto result = find(root()->l, pos);
        if (result == nullptr) {
            return end();
        }
        return const_iterator(result);
    }

    base_node* lower_bound(base_node* v, T const& pos) const {
        if (v == nullptr) return nullptr;

        T const& x = static_cast<node*>(v)->data;
        if (x < pos) return lower_bound(v->r, pos);
        if (!(x < pos) && !(pos < x)) return v;

        base_node* go_left;
        if ((go_left = lower_bound(v->l, pos))== nullptr) {
            return v;
        }
        const T& value = static_cast<node*>(go_left)->data;
        if (!(value < pos)) {
            return go_left;
        }
        return v;
    }
    const_iterator lower_bound(value_type const& pos) const {
        if (empty()) return end();
        auto v = lower_bound(root()->l, pos);
        if (v != nullptr) return const_iterator(v);
        else return end();
    }

    const_iterator upper_bound(value_type const& pos) const {
        if (empty()) return end();

        auto cur = find(pos);
        if (cur == end()) return lower_bound(pos);
        return ++const_iterator(cur);
    }

    static base_node* get_down(base_node *v) {
        return (v->l == nullptr ? v : get_down(v->l));
    }
    static base_node* get_up(base_node *v) {
        return (v->r == nullptr ? v : get_up(v->r));
    }

    static base_node* next(base_node *v) {
        if (v->r != nullptr) return get_down(v->r);
        auto pr = v->parent;
        for (; pr != nullptr && v == pr->r; v = pr, pr = pr->parent);
        return pr;
    }

    static base_node* prev(base_node *v) {
        if (v->l != nullptr) return get_up(v->l);
        auto pr = v->parent;
        for (; pr != nullptr && v == pr->l; v = pr, pr = pr->parent);
        return pr;
    }
};

template<typename T>
void swap(set<T>& first, set<T>& second) noexcept {
    std::swap(first.fake, second.fake);
    if (first.root()->l != nullptr) {
        first.root()->l->parent = &first.fake;
    }
    if (second.root()->l != nullptr) {
        second.root()->l->parent = &second.fake;
    }
}

#endif