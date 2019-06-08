//
// Created by Erika on 06.06.2019.
//

#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <vector>
#include <memory>
#include "huffman.h"

typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned char uchar;

class tree {
public:
    tree() = default;
    ~tree();
    explicit tree(std::vector<std::pair<uchar, ull>> &table);
    void to_root();
    bool go(uint c);
    bool is_term();
    uchar get();

private:
    void del();
    struct node;
    node *root = nullptr;
    node *cur = nullptr;
};

#endif //HUFFMAN_TREE_H
