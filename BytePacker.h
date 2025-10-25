#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>

class BytePacker
{
private:
    uint8_t* buffer;
    size_t buffer_size;
    size_t byte_index;

    bool canWrite(size_t bytes) const
    {
        return byte_index + bytes <= buffer_size;
    }

public:
    BytePacker(uint8_t* buf, size_t size)
        : buffer(buf), buffer_size(size), byte_index(0) {}

    size_t position() const { return byte_index; }
    size_t capacity() const { return buffer_size; }

    bool packUint8(uint8_t value)
    {
        if (!canWrite(1)) return false;
        buffer[byte_index++] = value;
        return true;
    }

    bool packUint16LE(uint16_t value)
    {
        if (!canWrite(2)) return false;
        buffer[byte_index++] = static_cast<uint8_t>(value);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 8);
        return true;
    }

    bool packUint16BE(uint16_t value)
    {
        if (!canWrite(2)) return false;
        buffer[byte_index++] = static_cast<uint8_t>(value >> 8);
        buffer[byte_index++] = static_cast<uint8_t>(value);
        return true;
    }

    bool packInt16LE(int16_t value) { return packUint16LE(static_cast<uint16_t>(value)); }
    bool packInt16BE(int16_t value) { return packUint16BE(static_cast<uint16_t>(value)); }

    bool packUint32LE(uint32_t value)
    {
        if (!canWrite(4)) return false;
        buffer[byte_index++] = static_cast<uint8_t>(value);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 8);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 16);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 24);
        return true;
    }

    bool packUint32BE(uint32_t value)
    {
        if (!canWrite(4)) return false;
        buffer[byte_index++] = static_cast<uint8_t>(value >> 24);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 16);
        buffer[byte_index++] = static_cast<uint8_t>(value >> 8);
        buffer[byte_index++] = static_cast<uint8_t>(value);
        return true;
    }

    bool packInt32LE(int32_t value) { return packUint32LE(static_cast<uint32_t>(value)); }
    bool packInt32BE(int32_t value) { return packUint32BE(static_cast<uint32_t>(value)); }

    bool packUint64LE(uint64_t value)
    {
        if (!canWrite(8)) return false;
        for (int i = 0; i < 8; ++i)
            buffer[byte_index++] = static_cast<uint8_t>(value >> (8 * i));
        return true;
    }

    bool packUint64BE(uint64_t value)
    {
        if (!canWrite(8)) return false;
        for (int i = 7; i >= 0; --i)
            buffer[byte_index++] = static_cast<uint8_t>(value >> (8 * i));
        return true;
    }

    bool packInt64LE(int64_t value) { return packUint64LE(static_cast<uint64_t>(value)); }
    bool packInt64BE(int64_t value) { return packUint64BE(static_cast<uint64_t>(value)); }

    bool packFloatLE(float value)
    {
        static_assert(sizeof(float) == 4);
        uint32_t temp;
        std::memcpy(&temp, &value, 4);
        return packUint32LE(temp);
    }

    bool packFloatBE(float value)
    {
        static_assert(sizeof(float) == 4);
        uint32_t temp;
        std::memcpy(&temp, &value, 4);
        return packUint32BE(temp);
    }

    bool packDoubleLE(double value)
    {
        static_assert(sizeof(double) == 8);
        uint64_t temp;
        std::memcpy(&temp, &value, 8);
        return packUint64LE(temp);
    }

    bool packDoubleBE(double value)
    {
        static_assert(sizeof(double) == 8);
        uint64_t temp;
        std::memcpy(&temp, &value, 8);
        return packUint64BE(temp);
    }
};
