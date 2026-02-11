zlibUncompress(l_uint8  *datain,
               size_t    nin,
               size_t   *pnout)
{
l_uint8  *dataout;
l_uint8  *bufferin, *bufferout;
l_int32   status;
size_t    nbytes;
BBUFFER  *bbin, *bbout;
z_stream  z;

    PROCNAME("zlibUncompress");

    if (!datain)
        return (l_uint8 *)ERROR_PTR("datain not defined", procName, NULL);

    if ((bufferin = (l_uint8 *)CALLOC(L_BUF_SIZE, sizeof(l_uint8))) == NULL)
        return (l_uint8 *)ERROR_PTR("bufferin not made", procName, NULL);
    if ((bufferout = (l_uint8 *)CALLOC(L_BUF_SIZE, sizeof(l_uint8))) == NULL)
        return (l_uint8 *)ERROR_PTR("bufferout not made", procName, NULL);

    if ((bbin = bbufferCreate(datain, nin)) == NULL)
        return (l_uint8 *)ERROR_PTR("bbin not made", procName, NULL);
    if ((bbout = bbufferCreate(NULL, 0)) == NULL)
        return (l_uint8 *)ERROR_PTR("bbout not made", procName, NULL);

    z.zalloc = (alloc_func)0;
    z.zfree = (free_func)0;

    z.next_in = bufferin;
    z.avail_in = 0;
    z.next_out = bufferout;
    z.avail_out = L_BUF_SIZE;

    inflateInit(&z);

    for ( ; ; ) {
        if (z.avail_in == 0) {
            z.next_in = bufferin;
            bbufferWrite(bbin, bufferin, L_BUF_SIZE, &nbytes);

            z.avail_in = nbytes;
        }
        if (z.avail_in == 0)
            break;
        status = inflate(&z, Z_SYNC_FLUSH);


        nbytes = L_BUF_SIZE - z.avail_out;
        if (nbytes) {
            bbufferRead(bbout, bufferout, nbytes);

        }
        z.next_out = bufferout;
        z.avail_out = L_BUF_SIZE;
    }

    inflateEnd(&z);

    bbufferDestroy(&bbin);
    dataout = bbufferDestroyAndSaveData(&bbout, pnout);

    FREE(bufferin);
    FREE(bufferout);
    return dataout;
}
