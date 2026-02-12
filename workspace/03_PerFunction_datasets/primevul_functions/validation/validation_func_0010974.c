memstreamCreateForRead(l_uint8  *indata,
                       size_t    insize)
{
L_MEMSTREAM  *mstream;

    mstream = (L_MEMSTREAM *)LEPT_CALLOC(1, sizeof(L_MEMSTREAM));
    mstream->buffer = indata;
    mstream->bufsize = insize;
    mstream->hw = insize;
    mstream->offset = 0;
    return mstream;
}
