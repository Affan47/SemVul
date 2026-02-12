int DateValue::read(const byte* buf, size_t len, ByteOrder )
    {

        if (len != 8) {
#ifndef SUPPRESS_WARNINGS
            EXV_WARNING << Error(kerUnsupportedDateFormat) << "\n";
#endif
            return 1;
        }

        char b[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        std::memcpy(b, reinterpret_cast<const char*>(buf), 8);
        int scanned = sscanf(b, "%4d%2d%2d",
                             &date_.year, &date_.month, &date_.day);
        if (scanned != 3) {
#ifndef SUPPRESS_WARNINGS
            EXV_WARNING << Error(kerUnsupportedDateFormat) << "\n";
#endif
            return 1;
        }
        return 0;
    }
