zvoid *memset(buf, init, len)
    register zvoid *buf;
    register int init;
    register unsigned int len;
{
    zvoid *start;

    start = buf;
    while (len--)
        *((char *)buf++) = (char)init;
    return start;
}
