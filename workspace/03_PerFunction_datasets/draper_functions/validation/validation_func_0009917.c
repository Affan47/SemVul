jpgDecode_getHeaderBufSize (
    IP_XFORM_HANDLE  hXform,
    DWORD           *pdwInBufLen)
{
    PJDEC_INST g;

    HANDLE_TO_PTR (hXform, g);
    *pdwInBufLen = MAX_HEADER_SIZE;
    return IP_DONE;

    fatal_error:
    return IP_FATAL_ERROR;
}
