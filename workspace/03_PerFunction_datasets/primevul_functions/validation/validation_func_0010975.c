tiffWriteCallback(thandle_t  handle,
                  tdata_t    data,
                  tsize_t    length)
{
L_MEMSTREAM  *mstream;
size_t        newsize;


    mstream = (L_MEMSTREAM *)handle;
    if (mstream->offset + length > mstream->bufsize) {
        newsize = 2 * (mstream->offset + length);
        mstream->buffer = (l_uint8 *)reallocNew((void **)&mstream->buffer,
                                                mstream->hw, newsize);
        mstream->bufsize = newsize;
    }

    memcpy(mstream->buffer + mstream->offset, data, length);
    mstream->offset += length;
    mstream->hw = L_MAX(mstream->offset, mstream->hw);
    return length;
}
