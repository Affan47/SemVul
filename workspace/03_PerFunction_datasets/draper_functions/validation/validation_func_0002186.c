isNumber(const String& val)
    {
        StringStream str(val);
        if (msUseLocale)
            str.imbue(msLocale);
        float tst;
        str >> tst;
        return !str.fail() && str.eof();
    }
