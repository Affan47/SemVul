fpixCreate(l_int32  width,
           l_int32  height)
{
l_float32  *data;
FPIX       *fpixd;

    PROCNAME("fpixCreate");

    if (width <= 0)
        return (FPIX *)ERROR_PTR("width must be > 0", procName, NULL);
    if (height <= 0)
        return (FPIX *)ERROR_PTR("height must be > 0", procName, NULL);

    if ((fpixd = (FPIX *)CALLOC(1, sizeof(FPIX))) == NULL)
        return (FPIX *)ERROR_PTR("CALLOC fail for fpixd", procName, NULL);
    fpixSetDimensions(fpixd, width, height);
    fpixSetWpl(fpixd, width);
    fpixd->refcount = 1;

    data = (l_float32 *)CALLOC(4 * width * height, sizeof(l_float32));
    if (!data)
        return (FPIX *)ERROR_PTR("CALLOC fail for data", procName, NULL);
    fpixSetData(fpixd, data);

    return fpixd;
}
