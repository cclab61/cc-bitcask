#ifndef MINIBITCASK_HPP
#define MINIBITCASK_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <memory>

namespace cc_bitcask
{
    class MiniBitcask
    {
    public:
        MiniBitcask(const std::string &dirPath);

        static std::unique_ptr<MiniBitcask> Open(const std::string &dirPath);

    private:
        std::string dirPath_;
    };
}

#endif
