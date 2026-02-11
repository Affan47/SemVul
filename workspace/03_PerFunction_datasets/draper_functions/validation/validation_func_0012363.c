dstrcpyf(dstr_t *ds, const char *src, ...)
{
    va_list ap;
    size_t srclen;

    va_start(ap, src);
    srclen = vsnprintf(ds->data, ds->alloc, src, ap);
    va_end(ap);

    if (srclen >= ds->alloc) {
        do {
            ds->alloc *= 2;
        } while (srclen >= ds->alloc);
        ds->data = realloc(ds->data, ds->alloc);

        va_start(ap, src);
        vsnprintf(ds->data, ds->alloc, src, ap);
        va_end(ap);
    }

    ds->len = srclen;
}
