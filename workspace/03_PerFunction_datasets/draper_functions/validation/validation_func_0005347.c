dSncat(String *dest, const char *src, int n, const char *file, int line)
{
    int oldlen = dest->len;
    int len = strlen(src);

    if (n < 0) core("dSncat: n==%ld", file, line, (long)n);
    if (n > len) n = len;
    dest->len += n;
    lcheck(dest, file, line);
    memcpy(dest->data + oldlen, src, n);
    dest->data[dest->len] = '\0';
    if (dest->charattrs) extend_charattrs(dest, oldlen, 0);
    return dest;
}
