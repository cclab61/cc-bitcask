#ifndef CC_BITCASK_DB_HPP
#define CC_BITCASK_DB_HPP

#include <iostream>
#include <memory>
#include <mutex>
#include <string>

namespace cc_bitcask {
class MiniBitcask {
   public:
    MiniBitcask(const std::string &dirPath);

    static std::unique_ptr<MiniBitcask> Open(const std::string &dirPath);

   private:
    std::string dirPath_;
};
}  // namespace cc_bitcask

#endif
