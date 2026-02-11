readHeaderMemTiff(const l_uint8  *cdata,
                  size_t          size,
                  l_int32         n,
                  l_int32        *pwidth,
                  l_int32        *pheight,
                  l_int32        *pbps,
                  l_int32        *pspp,
                  l_int32        *pres,
                  l_int32        *pcmap,
                  l_int32        *pformat)
{
l_uint8  *data;
l_int32   i, ret;
TIFF     *tif;

    PROCNAME("readHeaderMemTiff");

    if (!cdata)
        return ERROR_INT("cdata not defined", procName, 1);
    if (!pwidth || !pheight || !pbps || !pspp)
        return ERROR_INT("input ptr(s) not all defined", procName, 1);
    *pwidth = *pheight = *pbps = *pspp = 0;
    if (pres) *pres = 0;
    if (pcmap) *pcmap = 0;
    if (pformat) *pformat = 0;


    data = (l_uint8 *)cdata;
    if ((tif = fopenTiffMemstream("tifferror", "r", &data, &size)) == NULL)
        return ERROR_INT("tiff stream not opened", procName, 1);

    for (i = 0; i < n; i++) {
        if (TIFFReadDirectory(tif) == 0) {
            TIFFClose(tif);
            return ERROR_INT("image n not found in file", procName, 1);
        }
    }

    ret = tiffReadHeaderTiff(tif, pwidth, pheight, pbps, pspp,
                             pres, pcmap, pformat);
    TIFFClose(tif);
    return ret;
}
