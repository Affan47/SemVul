ne_calloc(size_t len)
{
    void *ptr;
    DO_MALLOC(ptr, len);
    return memset(ptr, 0, len);
}
