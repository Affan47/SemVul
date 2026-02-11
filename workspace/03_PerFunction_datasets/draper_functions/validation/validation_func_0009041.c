strm_ival(s)

char *s;
{
    unsigned int i;
    unsigned char *b = (unsigned char *)s;


    i = b[1] | ((b[0] & 0x7f) << 8);
    if (b[0] & 0x80)
        i |= (-1 << 15);
    return ((int)i);
}
