readHeaderJpeg(const char  *filename,
               l_int32     *pw,
               l_int32     *ph,
               l_int32     *pspp,
               l_int32     *pycck,
               l_int32     *pcmyk)
{
l_int32  ret;
FILE    *fp;

    PROCNAME("readHeaderJpeg");

    if (!pw && !ph && !pspp && !pycck && !pcmyk)
        return ERROR_INT("no results requested", procName, 1);
    if (pw) *pw = 0;
    if (ph) *ph = 0;
    if (pspp) *pspp = 0;
    if (pycck) *pycck = 0;
    if (pcmyk) *pcmyk = 0;
    if (!filename)
        return ERROR_INT("filename not defined", procName, 1);

    if ((fp = fopenReadStream(filename)) == NULL)
        return ERROR_INT("image file not found", procName, 1);
    ret = freadHeaderJpeg(fp, pw, ph, pspp, pycck, pcmyk);
    fclose(fp);
    return ret;
}
