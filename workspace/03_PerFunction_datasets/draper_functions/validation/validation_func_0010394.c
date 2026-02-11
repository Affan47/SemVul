arrayFindEachSequence(const l_uint8  *data,
                      l_int32         datalen,
                      const l_uint8  *sequence,
                      l_int32         seqlen)
{
l_int32  start, offset, realoffset, found;
L_DNA   *da;

    PROCNAME("arrayFindEachSequence");

    if (!data || !sequence)
        return (L_DNA *)ERROR_PTR("data & sequence not both defined",
                                  procName, NULL);

    da = l_dnaCreate(0);
    start = 0;
    while (1) {
        arrayFindSequence(data + start, datalen - start, sequence, seqlen,
                          &offset, &found);
        if (found == FALSE)
            break;

        realoffset = start + offset;
        l_dnaAddNumber(da, realoffset);
        start = realoffset + seqlen;
        if (start >= datalen)
            break;
    }

    if (l_dnaGetCount(da) == 0)
        l_dnaDestroy(&da);
    return da;
}
