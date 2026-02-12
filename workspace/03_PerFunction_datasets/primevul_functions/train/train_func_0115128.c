float getFloat(const byte* buf, ByteOrder byteOrder)
    {


        static_assert(sizeof(float) == 4, "float type requires 4-byte IEEE 754 binary32 format");
        union {
            uint32_t ul_;
            float    f_;
        } u;
        u.ul_ = getULong(buf, byteOrder);
        return u.f_;
    }
