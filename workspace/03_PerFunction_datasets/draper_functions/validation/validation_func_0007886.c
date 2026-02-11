makeIdentifier(const String& code)
    {
        assert(code.length() <= 4 && "Characters after the 4th are being ignored");
        uint32 ret = 0;
        size_t c = std::min((size_t)4, code.length());
        for (size_t i = 0; i < c; ++i)
        {
            ret += (code.at(i) << (i * 8));
        }
        return ret;

    }
