getValueFromString(const char *str,
                                      const size_t pos,
                                      const size_t len,
                                      OFString &val)
{
    size_t newPos = pos;

    if ((str != NULL) && (len > 0) && (pos < len))
    {

        const char *p = str + pos;

        while ((newPos++ < len) && (*p != '\\'))
            p++;

        val.assign(str + pos, newPos - pos - 1);
    } else
        val.clear();
    return newPos;
}
