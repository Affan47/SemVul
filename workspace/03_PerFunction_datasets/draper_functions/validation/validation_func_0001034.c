sharps_u8_l1(char * dest, char * source) {
    char * p = dest;
    *p = *source;
    for (p++, source++; *(source - 1); p++, source++) {
        *p = *source;
        if (*source == '\x9F') *--p = '\xDF';
    }
    return dest;
}
