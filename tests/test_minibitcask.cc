//
// Created by first macbook of sunboy on 2024/6/8.
//
#include <gtest/gtest.h>

#include <thread>

#include "cc_bitcask/db.hpp"

using namespace cc_bitcask;

const string testdir = "./testdir";

vector<uint8_t> stringToUint8(string s) {
    vector<uint8_t> res;
    for (int i = 0; i < s.size(); i++) {
        res.push_back(static_cast<uint8_t>(s[i]));
    }
    return res;
}

string RstringToUint8(vector<uint8_t> b) {
    string res;
    for (int i = 0; i < b.size(); i++) {
        res += static_cast<char>(b[i]);
    }
    return res;
}
vector<Entry> pairToEntryList(vector<pair<string, string>> pairs) {
    vector<uint8_t> key;
    vector<uint8_t> value;
    vector<Entry> result;
    for (int i = 0; i < pairs.size(); i++) {
        key = stringToUint8(pairs[i].first);
        value = stringToUint8(pairs[i].second);
        result.emplace_back(key, value, static_cast<uint16_t>(i));
    }
    return result;
}

/*pass
TEST(TestDBFile, TestOpen) {
    auto handle = MiniBitcask::Open(testdir);
    ASSERT_NE(handle, nullptr);
}
*/

/*pass
TEST(TestDBFile, TestWriteAndReadSingle) {
    auto handle = MiniBitcask::Open(testdir);
    vector<pair<string, string>> pair = {{"1", "3"}, {"2", "5"}, {"4", "7"}};
    vector<Entry> entrylist = pairToEntryList(pair);
    const int num_threads = 3;
    for (int i = 0; i < num_threads; i++) {
        handle->write(entrylist[i]);
    }
    for (int i = 0; i < 3; i++) {
        Entry *e = handle->read(i * entrylist[0].GetSize());
    }
}
*/

TEST(TestDBFile, TestWriteAndReadMuti) {
    auto handle = MiniBitcask::Open(testdir);
    vector<pair<string, string>> pair = {{"1", "3"}, {"2", "5"}, {"4", "7"}};
    vector<Entry> entrylist = pairToEntryList(pair);
    const int num_threads = 3;
    thread threads[num_threads];
    for (int i = 0; i < num_threads; i++) {
        threads[i] =
            thread([&handle, &entrylist, i]() { handle->write(entrylist[i]); });
    }

    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    for (int i = 0; i < 3; i++) {
        Entry *e = handle->read(i * entrylist[0].GetSize());
        cout << "keys: " << e->KeySize << "values: " << e->ValueSize
             << "key: " << RstringToUint8(e->Key)
             << "values: " << RstringToUint8(e->Value) << endl;
    }
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}