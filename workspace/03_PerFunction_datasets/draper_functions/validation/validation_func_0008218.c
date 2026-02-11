saConcatenatePdf(SARRAY      *sa,
                 const char  *fileout)
{
l_uint8  *data;
l_int32   ret;
size_t    nbytes;

    PROCNAME("saConcatenatePdf");

    if (!sa)
        return ERROR_INT("sa not defined", procName, 1);
    if (!fileout)
        return ERROR_INT("fileout not defined", procName, 1);

    ret = saConcatenatePdfToData(sa, &data, &nbytes);
    if (ret)
        return ERROR_INT("pdf data not made", procName, 1);
    ret = l_binaryWrite(fileout, "w", data, nbytes);
    FREE(data);
    return ret;
}
