//
// Created by Erika on 08.06.2019.
//

#include <iostream>
#include <random>
#include "huffman.h"
#include "gtest/gtest.h"
#include <string>


const int dd = 1024 * 1024 * 3;

TEST(correctness, empty) {
    std::stringstream in(""), between, out;
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}


TEST(correctness, one_letter) {
    std::stringstream in("a"), between, out;
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, all_letters) {
    std::stringstream in("abcdefghijklmnopqrstuvwxyz"), between, out;
    std::string a, b;
    huffman::compress(in, between);
    a = between.str(), b = out.str();
    huffman::decompress(between, out);
    a = between.str(), b = out.str();
    EXPECT_EQ(in.str(), out.str());
}


TEST(corectness, keyboard) {
    std::stringstream in("`1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./!@#$%^&*()_+!\"№;%:?*()_+)"), between, out;
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, invalid) {
    std::stringstream in("abcde abcde"), out;
    EXPECT_FALSE(huffman::decompress(in, out));
}

TEST(corectness, one_char) {
    std::stringstream in, between, out;
    for (int i = 0; i < dd; i++) in << 'a';
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}


TEST(corectness, two_random_chars) {
    std::stringstream in, between, out;
    std::mt19937 rnd(19937);
    for (int i = 0; i < dd; i++) in << (char)('a' + rnd() % 2);
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, few_random_chars) {
    std::stringstream in, between, out;
    std::mt19937 rnd(19937);
    for (int i = 0; i < dd; i++) in << (char)(rnd() % 256);
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, big_random) {
    std::stringstream in, between, out;
    std::mt19937 rnd(19937);
    for (int i = 0; i < dd; i++) in << (char)(rnd() % 256);
    huffman::compress(in, between);
    huffman::decompress(between, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, composition) {
    std::stringstream in, between1, between2, out1, out2;
    std::mt19937 rnd(19937);
    for (int i = 0; i < dd; i++) in << (char)(rnd() % 255);

    huffman::compress(in, between1);
    huffman::decompress(between1, out1);

    huffman::compress(out1, between2);
    huffman::decompress(between2, out2);

    EXPECT_EQ(in.str(), out2.str());
}




