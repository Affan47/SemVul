read64(U64 * i64, const char *str)
{
    U64             i64p;
    unsigned int    u;
    int             sign = 0;
    int             ok = 0;

    zeroU64(i64);
    if (*str == '-') {
        sign = 1;
        str++;
    }

    while (*str && isdigit((unsigned char)(*str))) {
        ok = 1;
        u = *str - '0';
        multBy10(*i64, &i64p);
        *i64 = i64p;
        incrByU16(i64, u);
        str++;
    }
    if (sign) {
        i64->high = (uint32_t) ~i64->high;
        i64->low = (uint32_t) ~i64->low;
        incrByU16(i64, 1);
    }
    return ok;
}
