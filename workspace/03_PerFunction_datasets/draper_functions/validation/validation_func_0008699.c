write4(unsigned w)
{
#if _WIN32
    bool notnewline = w != 0x000A000D;
#else
    bool notnewline = true;
#endif
    if (doindent && !notlinehead && notnewline)
    {
        if (level)
        {
            reserve(level);
            for (size_t i=0; i<level; i++)
            {
                this->data[offset] = '\t';
                offset++;
            }
        }
        notlinehead = 1;
    }
    reserve(4);
    *(unsigned *)(this->data + offset) = w;
    offset += 4;
}
