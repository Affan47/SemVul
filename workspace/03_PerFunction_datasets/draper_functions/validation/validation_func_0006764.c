CharCount(Nc::UInt32 c) const
{
    unsigned int r = 0;
    const Nc::UInt32 *p = c_str();
    for (unsigned int i = 0; i < size(); ++i)
    {
        if (p[i] == c)
            r++;
    }
    return r;
}
