GetStructFieldBufSize(matvar_t *matvar, size_t *size)
{
    int err;
    size_t nBytes = 0, type_buf_size;
    size_t tag_size = 8, array_flags_size = 8;

    *size = 0;

    if ( matvar == NULL )
        return GetEmptyMatrixMaxBufSize(NULL, 2, size);


    nBytes += tag_size + array_flags_size;


    nBytes += tag_size;

    err = GetTypeBufSize(matvar, &type_buf_size);
    err |= SafeAdd(&nBytes, nBytes, type_buf_size);
    if ( err )
        return 1;

    *size = nBytes;
    return 0;
}
