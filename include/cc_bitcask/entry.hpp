#ifndef CC_BITCASK_ENTRY_HPP
#define CC_BITCASK_ENTRY_HPP

#include <cstdint>
#include <cstring>
#include <vector>

constexpr std::size_t entryHeaderSize = 10;

enum Mark : uint16_t { PUT, DEL };
namespace cc_bitcask {
class Entry {
   public:
    std::vector<uint8_t> Key;
    std::vector<uint8_t> Value;
    uint32_t KeySize;
    uint32_t ValueSize;
    uint16_t Mark;

    Entry(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value,
          uint16_t mark);

    std::int64_t GetSize() const;

    std::vector<uint8_t> Encode() const;

    static Entry Decode(const std::vector<uint8_t> &buf);
};
}  // namespace cc_bitcask
#endif
