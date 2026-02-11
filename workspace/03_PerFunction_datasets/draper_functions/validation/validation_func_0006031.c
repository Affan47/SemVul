fftplt(fitsfile **fptr,
           const char *filename,
           const char *tempname,
           int *status)


{
    if (*status > 0)
        return(*status);

    if ( ffinit(fptr, filename, status) )
        return(*status);

    ffoptplt(*fptr, tempname, status);

    return(*status);
}
