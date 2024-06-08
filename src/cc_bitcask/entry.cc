#include "cc_bitcask/entry.hpp"
namespace cc_bitcask {
// Constructor
Entry::Entry(const std::vector<uint8_t> &key, const std::vector<uint8_t> &value,
             uint16_t mark)
    : Key(key),
      Value(value),
      KeySize(static_cast<uint32_t>(key.size())),
      ValueSize(static_cast<uint32_t>(value.size())),
      Mark(mark) {}

// GetSize Method
std::int64_t Entry::GetSize() const {
    return static_cast<int64_t>(entryHeaderSize + KeySize + ValueSize);
}

// Encode Method
std::vector<uint8_t> Entry::Encode() const {
    std::vector<uint8_t> buf(GetSize());
    std::size_t offset = 0;

    uint32_t tempKeySize = KeySize;
    uint32_t tempValueSize = ValueSize;

    // Encode KeySize
    for (int i = 3; i >= 0; --i) {
        buf[offset + i] = KeySize & 0xFF;
        tempKeySize >>= 8;
    }
    offset += 4;

    // Encode ValueSize
    for (int i = 3; i >= 0; --i) {
        buf[offset + i] = ValueSize & 0xFF;
        tempValueSize >>= 8;
    }
    offset += 4;

    // Encode Mark
    buf[offset] = (Mark >> 8) & 0xFF;
    buf[offset + 1] = Mark & 0xFF;
    offset += 2;

    // Copy Key and Value
    std::copy(Key.begin(), Key.end(), buf.begin() + offset);
    offset += KeySize;
    std::copy(Value.begin(), Value.end(), buf.begin() + offset);

    return buf;
}

// Decode Method
Entry Entry::Decode(const std::vector<uint8_t> &buf) {
    std::size_t offset = 0;

    uint32_t KeySize = 0;
    for (int i = 0; i < 4; ++i) {
        KeySize = (KeySize << 8) | buf[offset + i];
    }
    offset += 4;

    uint32_t ValueSize = 0;
    for (int i = 0; i < 4; ++i) {
        ValueSize = (ValueSize << 8) | buf[offset + i];
    }
    offset += 4;

    uint16_t Mark = (buf[offset] << 8) | buf[offset + 1];
    offset += 2;

    std::vector<uint8_t> Key(buf.begin() + offset,
                             buf.begin() + offset + KeySize);
    offset += KeySize;

    std::vector<uint8_t> Value(buf.begin() + offset,
                               buf.begin() + offset + ValueSize);

    return Entry(Key, Value, Mark);
}
}  // namespace cc_bitcask