#include <iostream>
#include <string>
#include <vector>
#include "cc_bitcask/db.hpp"

using namespace std;
using namespace cc_bitcask;

vector<uint8_t> stringToUint8(const string& s) {
    return vector<uint8_t>(s.begin(), s.end());
}

string uint8ToString(const vector<uint8_t>& v) {
    return string(v.begin(), v.end());
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <dirPath>" << endl;
        return 1;
    }

    string dirPath = argv[1];
    auto db = MiniBitcask::Open(dirPath);
    if (!db) {
        cerr << "Failed to open database" << endl;
        return 1;
    }

    // write
    vector<uint8_t> key = stringToUint8("dbname");
    vector<uint8_t> value = stringToUint8("minibitcask2");
    Entry entry(key, value, 1);
    db->write(entry);

    // read
    Entry* readEntry = db->read(entry.GetSize() * 0);
    if (readEntry == nullptr) {
        cerr << "Failed to read data" << endl;
        return 1;
    }
    cout << "get value " << uint8ToString(readEntry->Value) << "." << endl;
    db->close();
    cout << "close minibitcask." << endl;

    return 0;
}
