ush makeword(b)
    ZCONST uch *b;
{


    return (ush)((b[1] << 8) | b[0]);
}
