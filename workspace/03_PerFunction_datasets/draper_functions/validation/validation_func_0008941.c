BitVector_Create(N_int bits, boolean clear)
{
    N_word  size;
    N_word  mask;
    N_word  bytes;
    wordptr addr;
    wordptr zero;

    size = BitVector_Size(bits);
    mask = BitVector_Mask(bits);
    bytes = (size + BV_HIDDENWORDS) << BV_Factor;
    addr = (wordptr) malloc((size_t) bytes);
    if (addr != NULL)
    {
        *addr++ = bits;
        *addr++ = size;
        *addr++ = mask;
        if (clear)
        {
            zero = addr;
            BIT_VECTOR_ZERO_WORDS(zero,size)
        }
    }
    return(addr);
}
