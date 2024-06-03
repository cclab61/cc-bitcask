#include "cc_bitcask/db.hpp"

namespace cc_bitcask {
MiniBitcask::MiniBitcask(const std::string &dirPath) : dirPath_(dirPath) {}

std::unique_ptr<MiniBitcask> MiniBitcask::Open(const std::string &dirPath) {
    try {
        return std::make_unique<MiniBitcask>(dirPath);
    } catch (const std::exception &e) {
        std::cerr << "Error opening MiniBitcask: " << e.what() << std::endl;
        return nullptr;
    }
}

}  // namespace cc_bitcask
