pixReadMemPng(const l_uint8  *cdata,
              size_t          size)
{
FILE  *fp;
PIX   *pix;

    PROCNAME("pixReadMemPng");

    if (!cdata)
        return (PIX *)ERROR_PTR("cdata not defined", procName, NULL);

#if HAVE_FMEMOPEN
    if ((fp = fmemopen((void *)cdata, size, "r")) == NULL)
        return (PIX *)ERROR_PTR("stream not opened", procName, NULL);
#else
    L_WARNING("work-around: writing to a temp file\n", procName);
    fp = tmpfile();
    fwrite(cdata, 1, size, fp);
    rewind(fp);
#endif
    pix = pixReadStreamPng(fp);
    fclose(fp);
    if (!pix) L_ERROR("pix not read\n", procName);
    return pix;
}
