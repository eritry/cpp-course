//
// Created by Erika on 06.06.2019.
//
#include "huffman.h"
#include "tree.h"

const size_t size = 2048;
uchar in_buffer[size];
uchar out_buffer[size];

size_t writing_length = 0;
ull stream = 0;

template <typename T>
void huffman::print(std::ostream &out, T x, bool f) {
    if (sizeof x + writing_length >= size) {
        out.write((char*)out_buffer, writing_length);
        writing_length = 0;
    }
    memcpy(out_buffer + writing_length, &x, sizeof x);
    writing_length += sizeof x;
    if (f) stream += 8 * sizeof x;
}

void huffman::count_in(std::istream &in, std::vector<ull> &table) {
    size_t cur_length = length(in);

    while(cur_length) {
        size_t reading_length = std::min(size, cur_length);
        cur_length -= reading_length;
        in.read((char*)in_buffer, reading_length);
        for (size_t i = 0; i < reading_length; i++) {
            table[in_buffer[i]]++;
        }
    }
}

bool huffman::count_out(std::istream &in, std::vector<ull> &table) {
    uint cnt = 0;
    if (!in) return false;
    in.read((char *)(&cnt), sizeof cnt);
    for (uint i = 0; i < cnt; i++) {
        uchar letter;
        ull count;
        if (!in) return false;
        in.read((char *) &letter, sizeof letter);

        if (!in) return false;
        in.read((char *) &count, sizeof count);
        table[letter] = count;
    }
    return true;
}

std::vector<std::pair<uchar, ull>> huffman::build(const std::vector<ull>& table) {
    std::vector<std::pair<uchar, ull>> result(256);

    std::set<std::pair<ull, uint>> letters;
    int cnt = 0;
    for (int i = 0; i < 256; i++) {
        if (table[i]) letters.insert({table[i], (uint)i}), cnt++;
    }
    uint p = 256;
    std::vector<std::pair<ull, uint>> parent(512, {(ull)-1, (uint)-1});
    while (letters.size() > 1) {
        auto x = *letters.begin();
        letters.erase(letters.begin());
        auto y = *letters.begin();
        letters.erase(letters.begin());

        parent[x.second] = {p, 0};
        parent[y.second] = {p, 1};

        letters.insert({x.first + y.first, p++});
    }

    for (int i = 0; i < 256; i++) {
        if (!table[i]) continue;
        std::vector<uint> bits;
        for (ull j = (ull)i; parent[j].first != (ull)-1; j = parent[j].first) {
            bits.push_back(parent[j].second);
        }
        reverse(all(bits));

        ull ans = 0;
        for (auto bit : bits) {
            ans = (ans << 1) + bit;
        }
        if (cnt == 1) result[i] = {1, 1};
        else result[i] = {bits.size(), ans};
    }

    return result;
}

void huffman::compress(std::istream &in, std::ostream &out) {
    stream = 0;
    writing_length = 0;

    std::vector<ull> table(257, 0);
    count_in(in, table);

    uint cnt = 0;
    for (uint c = 0; c < 256; c++) {
        if (table[c]) cnt++;
    }

    print(out, stream);
    print(out, cnt);

    for (uint c = 0; c < 256; c++) if (table[c]) {
            print(out, (uchar)c);
            print(out, table[c]);
        }
    stream = 0;
    std::vector<std::pair<uchar, ull>> bin = build(table);

    ull bit = 0;
    uint bit_count = 0;

    size_t cur_length = length(in);
    while (cur_length) {
        size_t reading_length = std::min(size, cur_length);
        cur_length -= reading_length;
        in.read((char*)in_buffer, reading_length);

        for (size_t i = 0; i < reading_length; i++) {
            ull code = reversed(bin[in_buffer[i]]);
            bit |= code << bit_count;
            bit_count += bin[in_buffer[i]].first;

            if (bit_count >= 64) {
                print(out, bit);
                bit_count -= 64;
                bit = code >> (bin[in_buffer[i]].first - bit_count);
            }
        }
    }

    if (bit_count != 0) {
        print(out, bit);
        stream -= 64 - bit_count;
    }

    if (writing_length != 0) {
        out.write((char*) out_buffer, writing_length);
    }

    out.seekp(0);
    out.write((char*) &stream, sizeof stream);
}

bool huffman::decompress(std::istream &in, std::ostream &out) {
    stream = 0;
    writing_length = 0;
    std::vector<ull> table(257, 0);

    in.seekg(std::istream::beg);
    if (!in) return false;
    in.read((char*)&stream, sizeof stream);

    if (!count_out(in, table)) return false;
    std::vector<std::pair<uchar, ull>> bin = huffman::build(table);

    tree bor(bin);

    if (!in) return false;
    long long len = in.readsome((char*)in_buffer, size);
    bor.to_root();
    while (len > 0) {
        for (size_t i = 0; i < (size_t)len; i++) {
            for (uint bit = 0; bit < std::min<ull>(8, stream); bit++) {
                if (!bor.go((in_buffer[i] >> bit) & 1u)) {
                    return false;
                }
                if (bor.is_term()) {
                    uchar c = bor.get();
                    print(out, c, 0);
                    bor.to_root();
                }
            }
            if (stream >= 8) stream = stream - 8;
            else stream = 0;
        }
        if (!in) return false;
        len = in.readsome((char*)in_buffer, size);
    }

    if (writing_length != 0) {
        out.write((char*) out_buffer, writing_length);
    }
    return true;
}

size_t huffman::length(std::istream &in) {
    in.seekg(std::istream::beg);
    in.seekg(0, std::istream::end);
    size_t cur_length = (size_t)in.tellg();
    in.seekg(std::istream::beg);
    return cur_length;
}

ull huffman::reversed(std::pair<uchar, ull> &p) {
    ull rev = 0;
    uchar cnt = p.first; ull bin = p.second;
    for (uint i = 0; i < cnt; i++) {
        rev |= ((bin >> i) & 1u) << (cnt - i - 1);
    }
    return rev;
}
