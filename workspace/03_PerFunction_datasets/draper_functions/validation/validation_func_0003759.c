WriteMemDataMD5(
    TFileStream * pStream,
    ULONGLONG RawDataOffs,
    void * pvRawData,
    DWORD dwRawDataSize,
    DWORD dwChunkSize,
    LPDWORD pcbTotalSize)
{
    hash_state md5_state;
    unsigned char * md5_array;
    unsigned char * md5;
    LPBYTE pbRawData = (LPBYTE)pvRawData;
    DWORD dwBytesRemaining = dwRawDataSize;
    DWORD dwMd5ArraySize = 0;
    int nError = ERROR_SUCCESS;


    md5_array = md5 = AllocateMd5Buffer(dwRawDataSize, dwChunkSize, &dwMd5ArraySize);
    if(md5_array == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;


    while(dwBytesRemaining != 0)
    {

        dwChunkSize = STORMLIB_MIN(dwBytesRemaining, dwChunkSize);


        md5_init(&md5_state);
        md5_process(&md5_state, (unsigned char *)pbRawData, dwChunkSize);
        md5_done(&md5_state, md5);
        md5 += MD5_DIGEST_SIZE;


        dwBytesRemaining -= dwChunkSize;
        pbRawData += dwChunkSize;
    }


    RawDataOffs += dwRawDataSize;
    if(!FileStream_Write(pStream, &RawDataOffs, md5_array, dwMd5ArraySize))
        nError = GetLastError();


    if(pcbTotalSize != NULL)
        *pcbTotalSize = dwRawDataSize + dwMd5ArraySize;


    FREEMEM(md5_array);
    return nError;
}
