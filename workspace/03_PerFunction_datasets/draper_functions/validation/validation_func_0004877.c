_jxr_rbitstream_uint8(struct rbitstream*str)
{
    uint8_t tmp;
    int idx;

    if (str->bits_avail == 0)
        get_byte(str);

    if (str->bits_avail == 8) {
        str->bits_avail = 0;
        return str->byte;
    }

    tmp = 0;
    for (idx = 0 ; idx < 8 ; idx += 1) {
        tmp <<= 1;
        tmp |= _jxr_rbitstream_uint1(str);
    }

    return tmp;
}
