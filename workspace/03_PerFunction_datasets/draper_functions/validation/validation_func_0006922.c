generateUncompressedPS(char      *hexdata,
                       l_int32    w,
                       l_int32    h,
                       l_int32    d,
                       l_int32    psbpl,
                       l_int32    bps,
                       l_float32  xpt,
                       l_float32  ypt,
                       l_float32  wpt,
                       l_float32  hpt,
                       l_int32    boxflag)
{
char    *outstr;
char     bigbuf[L_BUF_SIZE];
SARRAY  *sa;

    PROCNAME("generateUncompressedPS");

    if (!hexdata)
        return (char *)ERROR_PTR("hexdata not defined", procName, NULL);

    if ((sa = sarrayCreate(0)) == NULL)
        return (char *)ERROR_PTR("sa not made", procName, NULL);
    sarrayAddString(sa, (char *)"%!Adobe-PS", L_COPY);
    if (boxflag == 0) {
        sprintf(bigbuf,
            "%%%%BoundingBox: %7.2f %7.2f %7.2f %7.2f",
            xpt, ypt, xpt + wpt, ypt + hpt);
        sarrayAddString(sa, bigbuf, L_COPY);
    } else {
        sarrayAddString(sa, (char *)"gsave", L_COPY);
    }

    if (d == 1)
        sarrayAddString(sa,
              (char *)"{1 exch sub} settransfer    %invert binary", L_COPY);

    sprintf(bigbuf, "/bpl %d string def         %%bpl as a string", psbpl);
    sarrayAddString(sa, bigbuf, L_COPY);
    sprintf(bigbuf,
           "%7.2f %7.2f translate         %%set image origin in pts", xpt, ypt);
    sarrayAddString(sa, bigbuf, L_COPY);
    sprintf(bigbuf,
            "%7.2f %7.2f scale             %%set image size in pts", wpt, hpt);
    sarrayAddString(sa, bigbuf, L_COPY);
    sprintf(bigbuf,
            "%d %d %d                 %%image dimensions in pixels", w, h, bps);
    sarrayAddString(sa, bigbuf, L_COPY);
    sprintf(bigbuf,
            "[%d %d %d %d %d %d]     %%mapping matrix: [w 0 0 -h 0 h]",
            w, 0, 0, -h, 0, h);
    sarrayAddString(sa, bigbuf, L_COPY);

    if (boxflag == 0) {
        if (d == 1 || d == 8)
            sarrayAddString(sa,
                (char *)"{currentfile bpl readhexstring pop} image", L_COPY);
        else
            sarrayAddString(sa,
              (char *)"{currentfile bpl readhexstring pop} false 3 colorimage",
              L_COPY);
    } else {
        if (d == 1 || d == 8)
            sarrayAddString(sa,
              (char *)"{currentfile bpl readhexstring pop} bind image", L_COPY);
        else
            sarrayAddString(sa,
          (char *)"{currentfile bpl readhexstring pop} bind false 3 colorimage",
                 L_COPY);
    }

    sarrayAddString(sa, hexdata, L_INSERT);

    if (boxflag == 0)
        sarrayAddString(sa, (char *)"\nshowpage", L_COPY);
    else
        sarrayAddString(sa, (char *)"\ngrestore", L_COPY);

    if ((outstr = sarrayToString(sa, 1)) == NULL)
        return (char *)ERROR_PTR("outstr not made", procName, NULL);

    sarrayDestroy(&sa);
    return outstr;
}
