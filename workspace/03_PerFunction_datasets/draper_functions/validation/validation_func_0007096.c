getObjectDataCallback(int bufferSize, const char *buffer,
                                      void *callbackData)
{
    struct buffer_pointer *bp = callbackData;
    unsigned int len = (bp->len < bufferSize) ? bp->len : bufferSize;

    memcpy((char *)bp->buf + bp->offset, (char *)buffer, len);
    bp->offset += len;
    bp->len -= len;
    return ((bp->len <= 0) ? S3StatusAbortedByCallback : S3StatusOK);
}
