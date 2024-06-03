#include <iostream>
#include <string>

#include "cc_bitcask/db.hpp"

int main() {
    std::string dirPath = "./data";
    auto db = cc_bitcask::MiniBitcask::Open(dirPath);
    if (!db) {
        std::cerr << "Failed to open database" << std::endl;
        return 1;
    }

    return 0;
}
