long DateValue::copy(byte* buf, ByteOrder ) const
    {

        char temp[9];

        int wrote = sprintf(temp, "%04d%02d%02d", date_.year, date_.month, date_.day);
        assert(wrote == 8);
        std::memcpy(buf, temp, wrote);
        return wrote;
    }
