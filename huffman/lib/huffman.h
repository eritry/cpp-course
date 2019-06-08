//
// Created by Erika on 06.06.2019.
//

#ifndef HUFFMAN_HUFFMAN_H
#define HUFFMAN_HUFFMAN_H

#define all(v) v.begin(), v.end()
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>

typedef unsigned int uint;
typedef unsigned long long ull;
typedef unsigned char uchar;

class huffman {
public:
    huffman() = default;

    static void compress(std::istream &in, std::ostream &out);

    static bool decompress(std::istream &in, std::ostream &out);

private:
    static void count_in(std::istream &in, std::vector<ull> &table);

    static bool count_out(std::istream &in, std::vector<ull> &table);

    template<typename T>
    static void print(std::ostream &out, T x, bool f = true);

    static std::vector<std::pair<uchar, ull>> build(const std::vector<ull> &table);

    static size_t length(std::istream &in);

    static ull reversed(std::pair<uchar, ull> &p);
};


#endif //HUFFMAN_HUFFMAN_H
