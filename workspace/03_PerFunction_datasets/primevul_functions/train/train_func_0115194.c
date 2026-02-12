int DataValue::read(const byte* buf, size_t len, ByteOrder )
    {

        value_.assign(buf, buf + len);
        return 0;
    }
