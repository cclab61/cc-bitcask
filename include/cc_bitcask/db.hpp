#ifndef CC_BITCASK_DB_HPP
#define CC_BITCASK_DB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <sys/stat.h>  //use for chmod
#include <math.h>
#include "entry.hpp"

using namespace std;

namespace cc_bitcask {

const size_t max_read_buffer_num = 512;

class MiniBitcask {
   private:
    /* Todo
    class InterMemTable {// this is the partial feature of db not handle
       private:
        vector<uint8_t> key_;
        string filename_;  // use entry mark to serve as file_id checker
        uint32_t valuesz_;
        size_t offset;
       public:
        InterMemTable();
    };
   */
   private:
    class BitcaskHanlde {
       private:
        string dirPath_;
        fstream fd_;
        shared_mutex mutex;
        size_t offset_;
       public:
        BitcaskHanlde(const string &dirPath, fstream fd, size_t offset);
        ~BitcaskHanlde();
        void write(Entry entry);
        Entry *read(size_t offset);
        bool isActive();
        void close();
    };

   private:
    BitcaskHanlde handle;  // the function of sharing handle is the task of db

   public:
    static shared_ptr<BitcaskHanlde> Open(const string &dirPath);
    static string find_active(const string &dirPath);
};

string join_path(const string &dirpath,const string &filename);

}  // namespace cc_bitcask

#endif