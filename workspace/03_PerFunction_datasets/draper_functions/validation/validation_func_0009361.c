strncpy_tochar(char *dest, const char *src, size_t max, const char *stopchars)
{
    const char *psrc = src;
    char *pdest = dest;
    if (isempty(psrc)) {
       return NULL;
    }
    while (*psrc && --max > 0 && !strchr(stopchars, *psrc)) {
        *pdest = *psrc;
        pdest++;
        psrc++;
    }
    *pdest = '\0';
    return psrc +1;
}
