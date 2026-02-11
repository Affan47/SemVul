tifDecode_convert (
    IP_XFORM_HANDLE hXform,
    DWORD           dwInputAvail,
    PBYTE           pbInputBuf,
    PDWORD          pdwInputUsed,
    PDWORD          pdwInputNextPos,
    DWORD           dwOutputAvail,
    PBYTE           pbOutputBuf,
    PDWORD          pdwOutputUsed,
    PDWORD          pdwOutputThisPos)
{
    PTIF_INST g;
    UINT      n;

    HANDLE_TO_PTR (hXform, g);


    if (pbInputBuf == NULL) {
        PRINT (_T("tif_decode_convert_row: Told to flush.\n"), 0, 0);
        *pdwInputUsed = *pdwOutputUsed = 0;
        *pdwInputNextPos  = g->dwInNextPos;
        *pdwOutputThisPos = g->dwOutNextPos;
        return IP_DONE;
    }


    n = g->dwRawRowBytes;

    if (dwInputAvail < n) {

        g->dwInNextPos   += dwInputAvail;
        *pdwInputNextPos  = g->dwInNextPos;
        *pdwInputUsed     = dwInputAvail;
        *pdwOutputUsed    = 0;
        *pdwOutputThisPos = g->dwOutNextPos;
        return IP_READY_FOR_DATA;
    }

    INSURE (dwOutputAvail >= n);
    memcpy (pbOutputBuf, pbInputBuf, n);

    if (g->bByteSwap && g->iBitsPerSample==16) {

        BYTE *pb, *pbAfter, b;
        pbAfter = pbInputBuf + n;
        for (pb=pbInputBuf; pb<pbAfter; pb+=4) {

            b = pb[0];  pb[0] = pb[1];  pb[1] = b;
            b = pb[2];  pb[2] = pb[3];  pb[3] = b;
        }
    }

    *pdwOutputUsed    = n;
    *pdwOutputThisPos = g->dwOutNextPos;
    g->dwOutNextPos  += n;

    g->dwInNextPos   += n;
    *pdwInputNextPos  = g->dwInNextPos;
    *pdwInputUsed     = n;
    g->dwRowsDone += 1;

    return IP_CONSUMED_ROW | IP_PRODUCED_ROW | IP_READY_FOR_DATA;

    fatal_error:
    return IP_FATAL_ERROR;
}
