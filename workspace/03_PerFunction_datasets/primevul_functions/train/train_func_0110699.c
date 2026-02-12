GetEmptyMatrixMaxBufSize(const char *name, int rank, size_t *size)
{
    int err = 0;
    size_t nBytes = 0, len, rank_size;
    size_t tag_size = 8, array_flags_size = 8;


    nBytes += tag_size + array_flags_size;


    if ( NULL != name )
        len = strlen(name);
    else
        len = 4;

    if ( len <= 4 ) {
        nBytes += tag_size;
    } else {
        nBytes += tag_size;
        if ( len % 8 ) {
            err = Add(&len, len, 8 - len % 8);
            if ( err )
                return err;
        }

        err = Add(&nBytes, nBytes, len);
        if ( err )
            return err;
    }


    err = Mul(&rank_size, rank, 4);
    if ( err )
        return err;
    if ( rank % 2 )
        err = Add(&nBytes, nBytes, tag_size + 4);
    else
        err = Add(&nBytes, nBytes, tag_size);
    if ( err )
        return err;

    err = Add(&nBytes, nBytes, rank_size);
    if ( err )
        return err;

    err = Add(&nBytes, nBytes, tag_size);
    if ( err )
        return err;

    *size = nBytes;
    return MATIO_E_NO_ERROR;
}
