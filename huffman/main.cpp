#include <iostream>
#include <string>
#include <fstream>
#include "lib/huffman.h"

int main(int argc, char *argv[]) {
    const std::string usage = "usage: ./huffman <-c | -d> in out\n -c : compress, -d : decompress";

    if (argc != 4) {
        std::cout << usage;
        return 0;
    }

    std::string flag = std::string(argv[1]);
    std::string from = std::string(argv[2]);
    std::string to = std::string(argv[3]);

    std::ifstream in(from, std::ifstream::binary);
    std::ofstream out(to, std::ofstream::binary);

    if (in.is_open() && out.is_open()) {
        if (flag == "-c") {
            huffman::compress(in, out);
        } else if (flag == "-d") {
            if (!huffman::decompress(in, out)) {
                std::cout << "Couldn't decompress file " + from + ".\n";
            }
        } else {
            std::cout << usage;
        }
    } else {
        if (!in.is_open()) std::cout << "Couldn't open file " + from + ".\n";
        if (!out.is_open()) std::cout << "Couldn't open file " + to + ".\n";
    }

    return 0;
}
