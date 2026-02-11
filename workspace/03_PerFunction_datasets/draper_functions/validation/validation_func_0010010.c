resizebytes(void *old, size_t oldsize, size_t newsize)
{
    void *ret;
    if (newsize < 1) newsize = 1;
    if (oldsize < 1) oldsize = 1;
    ret = (void *)realloc((char *)old, newsize);
    if (newsize > oldsize && ret)
        memset(((char *)ret) + oldsize, 0, newsize - oldsize);
#ifdef LOUD
    fprintf(stderr, "resize %lx %d --> %lx %d\n", (int)old, oldsize, (int)ret, newsize);
#endif
#ifdef DEBUGMEM
    totalmem += (newsize - oldsize);
#endif
    if (!ret)
        post("pd: resizebytes() failed -- out of memory");
    return (ret);
}
