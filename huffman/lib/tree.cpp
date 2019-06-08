//
// Created by Erika on 06.06.2019.
//

#include "tree.h"

struct tree::node {
    uchar data{};
    node *l = nullptr;
    node *r = nullptr;

    node() = default;

    explicit node(uchar _data, node *_l = nullptr, node *_r = nullptr) {
        data = _data, l = _l, r = _r;
    }
};

tree::tree(std::vector<std::pair<uchar, ull>> &bin) {
    root = new node();
    for (uint i = 0; i < 256; i++) {
        int cnt = bin[i].first;
        ull c = bin[i].second;
        cur = root;
        std::vector<ull> bits;
        while(cnt-- > 0) {
            bits.push_back(c & 1);
            c >>= 1;
        }
        std::reverse(all(bits));
        for (ull j : bits) {
            if (j) {
                if (!cur->r) cur->r = new node();
                cur = cur->r;
            } else {
                if (!cur->l) cur->l = new node();
                cur = cur->l;
            }
        }
        cur->data = (uchar)i;
    }
}

void tree::del() {
    node *prev = cur;
    if (cur->r) cur = cur->r, del(), cur = prev;
    if (cur->l) cur = cur->l, del(), cur = prev;
    delete cur;
}

tree::~tree() {
    cur = root;
    del();
}

bool tree::go(uint c) {
    cur = (c ? cur->r : cur->l);
    return (cur != nullptr);
}

bool tree::is_term() {
    return (!cur->l && !cur->r);
}

uchar tree::get() {
    return cur->data;
}

void tree::to_root() {
    cur = root;
}
