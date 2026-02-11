spifmem_malloc(const spif_charptr_t filename, unsigned long line, size_t size)
{
    void *temp;

#if MALLOC_CALL_DEBUG
    ++malloc_count;
    if (!(malloc_count % MALLOC_MOD)) {
        fprintf(LIBAST_DEBUG_FD, "Calls to malloc(): %d\n", malloc_count);
    }
#endif

    D_MEM(("%lu bytes requested at %s:%lu\n", size, NONULL(filename), line));

    temp = (void *) malloc(size);
    ASSERT_RVAL(!SPIF_PTR_ISNULL(temp), SPIF_NULL_TYPE(ptr));
    if (DEBUG_LEVEL >= DEBUG_MEM) {
        memrec_add_var(&malloc_rec, SPIF_CAST(charptr) NONULL(filename), line, temp, size);
    }
    return (temp);
}
