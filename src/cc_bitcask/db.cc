#include "cc_bitcask/db.hpp"
namespace fs = std::filesystem;

// Todo
// use max_active_file_threshold to control whether need to change current
// active file to be a old file, and create a new active file with a sequential
// id.

namespace cc_bitcask {

/*Todo
MiniBitcask::InterMemTable::InterMemTable(){
    key_ = {};
    filename_ = "";  // use entry mark to serve as file_id checker
    valuesz_ = 0;
    offset = 0;
}
*/

MiniBitcask::BitcaskHanlde::BitcaskHanlde(const string &dirPath, fstream fd,
                                          size_t offset)
    : dirPath_(dirPath), fd_(std::move(fd)), offset_(offset) {}
MiniBitcask::BitcaskHanlde::~BitcaskHanlde() {
    if (fd_.is_open()) {
        fd_.close();
    }
}
shared_ptr<MiniBitcask::BitcaskHanlde> MiniBitcask::Open(
    const string &dirPath) {
    // ignore the unique bitcask function now, it is the job of db
    // no check for path， just impl core task, and dirPath must be a directory
    fstream fd;
    string active_filename = join_path(dirPath, "1.active");
    if (!fs::exists(dirPath)) {  // if exists, we assume it's a dir
        fs::create_directory(dirPath);
        if (chmod(dirPath.c_str(), 0755) != 0) {
            cerr << "Failed to set dir permissions." << endl;
            return nullptr;
        }
        ofstream tmp(active_filename, ios::out | ios::binary);
        tmp.close();
        if (chmod(active_filename.c_str(), 0644) != 0) {
            cerr << "Failed to set active_filename permissions." << endl;
            return nullptr;
        }
    } else {
        active_filename = MiniBitcask::find_active(dirPath);
        if (active_filename.empty()) {
            cerr << "the active record file lost" << endl;
            return nullptr;
        }
    }
    fd = fstream(active_filename, ios::out | ios::in | ios::binary);
    return make_shared<BitcaskHanlde>(dirPath, std::move(fd),
                                      fs::file_size(active_filename));
}

Entry *MiniBitcask::BitcaskHanlde::read(size_t offset) {
    if (!fd_.is_open()) {
        cerr << "bitcaskHandle was closed" << endl;
        return nullptr;
    }
    fd_.seekp(offset);

    size_t byte_num = min(offset_ - offset, max_read_buffer_num);

    std::vector<char> buffer(byte_num);
    fd_.read(buffer.data(), byte_num);
    std::vector<uint8_t> decode_buffer(buffer.begin(), buffer.end());
    Entry *entry = new Entry(Entry::Decode(decode_buffer));
    return entry;
}

void MiniBitcask::BitcaskHanlde::write(Entry e) {
    if (!fd_.is_open()) {
        cerr << "bitcaskHandle was closed" << endl;
        return;
    }
    unique_lock<shared_mutex> lock(mutex);
    fd_.seekp(offset_);
    char buffer[e.GetSize()];
    std::memcpy(buffer, e.Encode().data(), e.GetSize());
    fd_.write(buffer, e.GetSize());
    offset_ += e.GetSize();
}

bool MiniBitcask::BitcaskHanlde::isActive() { return fd_.is_open(); }

void MiniBitcask::BitcaskHanlde::close() { return fd_.close(); }

string MiniBitcask::find_active(const string &dirPath) {
    for (const auto &entry : fs::directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry.path()) &&
            entry.path().extension() == ".active") {
            return entry.path();
        }
    }
    return "";
}

string join_path(const string &dirpath, const string &filename) {
    return dirpath.back() == '/' ? dirpath + filename
                                 : dirpath + "/" + filename;
}

}  // namespace cc_bitcask
