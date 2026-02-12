int flush(__G__ rawbuf, size, unshrink)
    __GDEF
    uch *rawbuf;
    ulg size;
    int unshrink;
#if (defined(USE_DEFLATE64) && defined(__16BIT__))
{
    int ret;


    while (size > 0x8000L) {
        ret = partflush(__G__ rawbuf, 0x8000L, unshrink);
        if (ret != PK_OK)
            return ret;
        size -= 0x8000L;
        rawbuf += (extent)0x8000;
    }
    return partflush(__G__ rawbuf, size, unshrink);
}
