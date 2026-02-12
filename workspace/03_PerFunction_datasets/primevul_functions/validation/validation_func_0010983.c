tiffSeekCallback(thandle_t  handle,
                 toff_t     offset,
                 l_int32    whence)
{
L_MEMSTREAM  *mstream;

    PROCNAME("tiffSeekCallback");
    mstream = (L_MEMSTREAM *)handle;
    switch (whence) {
        case SEEK_SET:

            if((size_t)offset != offset) {
                return (toff_t)ERROR_INT("too large offset value", procName, 1);
            }
            mstream->offset = offset;
            break;
        case SEEK_CUR:

            mstream->offset += offset;
            break;
        case SEEK_END:


            mstream->offset = mstream->hw - offset;
            break;
        default:
            return (toff_t)ERROR_INT("bad whence value", procName,
                                     mstream->offset);
    }

    return mstream->offset;
}
