pixGenerateJpegData(PIX     *pixs,
                    l_int32  ascii85flag,
                    l_int32  quality)
{
l_int32             d;
char               *tname;
L_COMPRESSED_DATA  *cid;

    PROCNAME("pixGenerateJpegData");

    if (!pixs)
        return (L_COMPRESSED_DATA *)ERROR_PTR("pixs not defined",
                                              procName, NULL);
    if (pixGetColormap(pixs))
        return (L_COMPRESSED_DATA *)ERROR_PTR("pixs has colormap",
                                              procName, NULL);
    d = pixGetDepth(pixs);
    if (d != 8 && d != 32)
        return (L_COMPRESSED_DATA *)ERROR_PTR("pixs not 8 or 32 bpp",
                                              procName, NULL);


    tname = genTempFilename("/tmp", "temp.jpg", 1, 1);
    pixWriteJpeg(tname, pixs, quality, 0);

    cid = l_generateJpegData(tname, ascii85flag);
    FREE(tname);
    return cid;
}
