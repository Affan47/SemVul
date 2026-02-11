l_generateJpegData(const char  *fname,
                   l_int32      ascii85flag)
{
l_uint8            *datacomp = NULL;
char               *data85 = NULL;
l_int32             w, h, xres, yres, bps, spp;
l_int32             nbytes85;
size_t              nbytescomp;
FILE               *fp;
L_COMPRESSED_DATA  *cid;

    PROCNAME("l_generateJpegData");

    if (!fname)
        return (L_COMPRESSED_DATA *)ERROR_PTR("fname not defined",
                                              procName, NULL);


    if ((datacomp = l_binaryRead(fname, &nbytescomp)) == NULL)
        return (L_COMPRESSED_DATA *)ERROR_PTR("datacomp not extracted",
                                              procName, NULL);


    if ((fp = fopenReadStream(fname)) == NULL)
        return (L_COMPRESSED_DATA *)ERROR_PTR("stream not opened",
                                              procName, NULL);
    freadHeaderJpeg(fp, &w, &h, &spp, NULL, NULL);
    bps = 8;
    fgetJpegResolution(fp, &xres, &yres);
    fclose(fp);


    if (ascii85flag == 1) {
        data85 = encodeAscii85(datacomp, nbytescomp, &nbytes85);
        FREE(datacomp);
        if (!data85)
            return (L_COMPRESSED_DATA *)ERROR_PTR("data85 not made",
                                                  procName, NULL);
        else
            data85[nbytes85 - 1] = '\0';
    }

    cid = (L_COMPRESSED_DATA *)CALLOC(1, sizeof(L_COMPRESSED_DATA));
    if (!cid)
        return (L_COMPRESSED_DATA *)ERROR_PTR("cid not made", procName, NULL);
    if (ascii85flag == 0)
        cid->datacomp = datacomp;
    else {
        cid->data85 = data85;
        cid->nbytes85 = nbytes85;
    }
    cid->type = L_JPEG_ENCODE;
    cid->nbytescomp = nbytescomp;
    cid->w = w;
    cid->h = h;
    cid->bps = bps;
    cid->spp = spp;
    cid->res = xres;
    return cid;
}
