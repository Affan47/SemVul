int XmpValue::read(const byte* buf,
                       size_t len,
                       ByteOrder )
    {
        std::string s(reinterpret_cast<const char*>(buf), len);
        return read(s);
    }
