tiffCloseCallback(thandle_t  handle)
{
L_MEMSTREAM  *mstream;

    mstream = (L_MEMSTREAM *)handle;
    if (mstream->poutdata) {
        *mstream->poutdata = mstream->buffer;
        *mstream->poutsize = mstream->hw;
    }
    LEPT_FREE(mstream);
    return 0;
}
