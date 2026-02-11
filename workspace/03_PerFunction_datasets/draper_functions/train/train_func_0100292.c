BitVector_MSB(wordptr addr, boolean bit)
{
    N_word size = BV_SIZE_(addr);
    N_word mask = BV_MASK_(addr);

    if (size-- > 0)
    {
        if (bit) *(addr+size) |= mask AND NOT (mask >> 1);
        else     *(addr+size) &= NOT mask OR (mask >> 1);
    }
}
