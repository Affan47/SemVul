extent uzmbclen(ptr)
    ZCONST unsigned char *ptr;
{
    int mbl;

    mbl = mblen((ZCONST char *)ptr, MB_CUR_MAX);


    return (extent)(mbl > 0 ? mbl : 1);
}
