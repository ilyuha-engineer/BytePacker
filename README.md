# BytePacker

`BytePacker` is a lightweight C++ utility class for packing primitive data types (`int`, `float`, `double`, etc.) into a raw byte buffer.  
It supports both **little-endian (LE)** and **big-endian (BE)** byte orders.

---

## ✨ Features

- Pack the following data types:
  - `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`
  - `int16_t`, `int32_t`, `int64_t`
  - `float`, `double`
- Supports **LE** and **BE** formats
- Built-in boundary check to prevent buffer overflow
- Safe handling of floating-point types using `memcpy`

---

## 🧩 Example Usage

```cpp
#include "BytePacker.h"
#include <iostream>

int main() {
    uint8_t buffer[32];
    BytePacker packer(buffer, sizeof(buffer));

    packer.packUint8(0x42);
    packer.packUint16LE(0x1234);
    packer.packUint32BE(0xDEADBEEF);
    packer.packFloatLE(3.14f);
    packer.packDoubleBE(6.283185307);

    std::cout << "Packed " << packer.position() << " bytes\n";
}
