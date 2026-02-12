void sdssubstr(sds s, size_t start, size_t len) {

    size_t oldlen = sdslen(s);
    if (start >= oldlen) start = len = 0;
    if (len > oldlen-start) len = oldlen-start;


    if (len) memmove(s, s+start, len);
    s[len] = 0;
    sdssetlen(s,len);
}
